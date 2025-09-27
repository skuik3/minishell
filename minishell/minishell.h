/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:38:30 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/27 18:35:05 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stddef.h>
# include <string.h>
# include <ctype.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include "helper_funcs/libft.h"

extern int  g_signal;

# define _GNU_SOURCE
# define MAX_TOKENS 256

# define SHELL_DEFAULT 00644
# define ERR_MALLOC  "Malloc failure\n"
# define ERR_ARG     "Not enough arguments\n"
# define ERR_FILE    "Error opening/creating a file\n"
# define ERR_NOTFILE "No such file or directory\n"
# define ERR_FORK    "Error forking\n"
# define ERR_BC      "Error\n" 
# define ERR_PIPE    "Error creating a pipe\n"
# define ERR_DUP     "Error duplicating\n"
# define ERR_READ    "Error reading\n"
# define ERR_EXEC    "Error executing file\n"
# define INVALID_PAR "Invalid parameter name\n"

typedef struct environment_variables
{
	char    **start;
	char    **mod;
	int     exit_status;
}	t_env;

typedef struct pipe
{
	int         *pipe;
	struct pipe *next;
}	t_pipe;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_REDIR_HEREDOC,
	T_END,
	T_OR,
	T_AND,
	T_BG,
}	t_token_type;

typedef struct s_token
{
	char            *value;
	t_token_type    type;
	struct s_token  *next;
}	t_token;


typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	char            *filename;
	t_redir_type    type; 
	int             *pipe_forhdc;
}	t_redir;

typedef struct s_command
{
	char                *command;
	int                 is_first;
	char                **arguments;
	t_redir             **redir_in;
	int                 redir_in_count;
	t_redir             **redir_out;
	int                 redir_out_count;
	struct s_command    *next;
	t_env               *envar;
	int                 orig_stdin;
	int                 orig_stdout;
}	t_command; 

typedef struct s_cmd_builder
{
	t_command   *cmd;
	t_list      *args;
	t_list      *redir_in;
	t_list      *redir_out;
}	t_cmd_builder;

typedef struct s_node
{
	void            *content;
	struct s_list   *next;
}	t_node;

typedef struct s_biggiest_struct
{
	t_command   *cmd;
	t_command   *cmd_head;
	t_env       *env;
	t_pipe      *pipe_cmd;
	t_pipe      *pipe_head;
	int         exit_status;
	int         exit_bef;
}	t_biggie;

typedef struct s_exp_data
{
	const char	*input;
	size_t		start;
	size_t		end;
	bool		expand;
}	t_exp_data;

typedef struct s_exp_vars
{
	char	*var_name;
	char	*var_value;
	char	*after;
	int		is_special_var;
}	t_exp_vars;

typedef struct s_parse_params
{
    const char  *input;
    size_t      i;
    t_token     **tokens;
    char        **result;
    t_env       *env;
    t_biggie    *bigs;
}   t_parse_params;

// ANEZKAS_PART
void	free_big(t_biggie *bigs);
void	clean_big(t_biggie *bigs);
void	free_arguments(char **arguments);
void	free_env(t_env *env);
void	free_redir(t_redir **redir);
void	free_commands(t_command *cmd);
void	free_pipes(t_pipe *pipe);
//main_execution
int			what_builtin(t_biggie *bigs);
t_env		*adding_env(t_command *cmd, char **envp);
int			command_execution(t_biggie *bigs);
int			single_command(t_biggie *bigs);
int			multiple_commands(t_biggie *bigs);
int			last_multiple(t_biggie *bigs);
int			other_multiple(t_biggie *bigs);
int			first_multiple(t_biggie *bigs);
void		put_orig(t_biggie *bigs, int orig_stdin, int orig_stdout);
t_biggie	*setting_big(void);
void		close_herepipe(t_command *cmd);
int			check_before_single(t_biggie *bigs);
void		close_pipes(t_biggie *bigs);
//utils for main_execution
int	saving_env(char ***env, char *envp[]);
int	is_builtint(char *command);
//signals
void	handle_signal_main(int signal);
void	handle_signal_child(int signal);
void	handle_signal_heredoc(int signal);
void	set_ctrl(struct sigaction sa);
//builtin fce
int	run_pwd(void);
int	run_echo(char **string);
int	run_cd(char **path, t_env *env); //todo home
int	run_env(t_biggie *bigs);
int	run_exit(t_biggie *bigs); //todo s ciselkami
int	run_export(t_biggie *bigs);
int	run_unset(t_env *envp, char **arguments);
//utils for builtin fce
int		copy_string(char **env, char *orig_env);
int		find_start(char *envp[], char *arguments);
int		counting_envlen(char **envp);
char	**put_envp(char **old_envp, char *new_arg);
int		get_order(char **envp);
char	*find_variable(char *arguments);
char	**put_unset(char **old_env, int unset);
int		unset_variable(char *envp, char *variable, int i);
char	*find_envar(t_env *env, char *find);
char	*find_path(t_env *env, char *find_var);
char	*adding_variable(char *argument);
int		variable_present(char *variable, t_env *envp);
char	**exchange_values(char **envp, char *exchange);
char	**prepare_unset(char *argument);
int		value_present(char *argument);
char	**adding_command(t_command *cmd);
int		just_nb(char *nb);
int		unset_value(t_env *envp, char *argument);
int		number_exit(char *args);
int		check_variable(char *variable);
int		unseting(t_env *envp, char *arguments);
int		find_unset(char *arguments, t_env *envp);
int		unset_position(char *envp, char *variable, int i);
int		export_argument(t_env *envp, char *argument, t_command *cmd);
int		inner_check(char *envp[], int i);
int		counting_envlen(char **envp);
//pipes
int		counting_pipes(t_command *cmd);
t_pipe	*prepare_pipes(t_command *cmd);
t_pipe	*creating_first_pipe(void);
t_pipe	*adding_pipe(t_pipe *pipe_cmd);
//redirect
int		redirect_out(t_command *cmd);
int		last_redirect_out(t_redir *last);
int		appending(t_redir *append);
int		redirecting_out(t_redir *redirout);
int		check_redirect(t_command *cmd);
int		redirecting_in(t_redir *redirin);
int		last_redirect_in(t_redir *last);
int		redirect_in(t_command *cmd);
int		heredoc_present(t_redir **redir);
int		check_heredoc (t_biggie *bigs);
int		do_heredoc(t_biggie *bigs);
char	*get_line_heredoc(t_redir *last);
int		last_heredoc(t_biggie *bigs, int i);
int		redirecting_heredoc(t_biggie *bigs, int i);
int		setting_pipe_hdc(t_biggie *bigs);
int		where_last_heredoc(t_command *cmd, int redi);
int		last_heredoc_multiple(t_biggie *bigs, int i);
int		do_heredoc_multiple(t_biggie *bigs);
int		child_heredoc(t_biggie *bigs, int i);
//nonbuiltins
int	executing(t_command *cmd);
//nonbuiltins utils
int		is_path(char *command);
char	*command_path(t_command *cmd);
//libft_later
int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_strlen(const char *str);
int				ft_numstrings(const char *s, int c);
unsigned int	findend(const char *s, int c, int i);
char			**ft_split(char const *s, char c);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
void			ft_putstr_fd(char *s, int fd);
int				ft_isalnum(int c);
int				sisalpha(int c);
void			free_pipes(t_pipe *pipe);
// SISIS_PART
//alloc_stuff.c
char	**alloc_str_array(t_list *list, int count);
t_redir	**alloc_redir_array(t_list *list, int count);
//free2.c
void	free_string_list(t_list *list);
//free.c
void	free_tokens(t_token *head);
void	free_array(char **arr);
void	free_cmd(t_command *cmd);
void	free_list(t_list *list);
//get_type.c
t_token			*new_token(const char *start, size_t len, t_token_type type);
t_redir			*new_redir(t_token *tok, t_redir_type type);
t_redir_type	get_redir_type_from_token(t_token_type tok_type);
t_redir_type	get_redir_type(const char *str, size_t len);
t_token_type	get_token_type_len(const char *str, size_t len);
//handle_and_check.c
bool	validate_syntax(t_token *tokens);
//list.c
void	add_redir_to_list(t_token *tok, t_redir *r, t_cmd_builder *b);
void	list_add_back(t_list **list, void *content);
int		list_size(t_list *list);
char	**list_to_str_array(t_list *list);
t_redir	**list_to_redir_array(t_list *list);
//p_tok_loop_helper.c
void	add_redir_token(t_token *tok, t_cmd_builder *b);
bool	is_invalid_token(t_token *tok);
bool	init_cmd_builder(t_cmd_builder *b, t_command **out);
char	*get_token_value(t_token *tok, t_env *env);
//parse_pipes
bool	init_commands(t_command **head, t_token *tokens, t_env *env);
//parse_tok_loop.c
bool	parse_tokens(t_token *tok, t_command **out, t_env *env);
//parse_token.c
size_t	parse_word(const char *input, size_t i, t_token **tokens);
size_t	parse_operator(const char *input, size_t i, t_token **tokens);
//parser_handle_token.c
void	handle_token(t_token *tok, t_cmd_builder *b);
//run_shell.c
t_command	*run_shell_line(char *line, t_env *env, t_biggie *bigs);
//secial_case.c
int		is_valid_var_char(char c, int is_first);
int		get_var_name_len(const char *str);
char	*extract_var_name(const char *str, int len);
char	*find_in_env_array(char **env, const char *var_name);
char	*get_env_var(t_env *env, const char *var_name);
//special_case2.c
char	*join_exp_parts(char *before, char *expansion, char *after);
char	*handle_no_exp(const char *input);
char	*handle_empty_var(char *before);
void	cleanup_vars(char *var_name, char *after, char *var_value,
			int is_special);
char	*build_exp_result(char *before, char *var_value, char *after);
//special_case3.c
char	*process_var(char *dollar_pos, char *before, t_env *env);
char	*expand_var(const char *input, t_env *env);
//tokenizing.c
void	append_token(t_token **head, t_token *new_tok);
bool	is_operator_start(char c);
size_t	skip_spaces(const char *input, size_t i);
void	append_seg_w_expans(char **result, t_exp_data data, t_env *env);
//tokenizing2.c
size_t	parse_word_w_env(t_parse_params *params);
//tokenizing3.c
t_token *tokenize(const char *input, t_env *env, t_biggie *bigs);

#endif