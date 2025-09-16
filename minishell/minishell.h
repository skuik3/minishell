/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:38:30 by anezkahavra       #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/09/11 22:37:53 by skuik            ###   ########.fr       */
=======
/*   Updated: 2025/09/15 13:58:07 by skuik            ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>


#include "tokenizer/helper_funcs/libft.h"

#define _GNU_SOURCE
#define MAX_TOKENS 256

//for readability
#define SHELL_DEFAULT 00644
#define ERR_MALLOC "Malloc failure\n"
#define ERR_ARG "Not enough arguments\n"

//structs
typedef struct environment_variables
{
    char **start;
    char **mod;
} env_t;


typedef enum e_token_type {
    T_WORD,       //hello
    T_PIPE,       // |
    T_END,         // end of str
    T_OR,        // ||
    T_AND,       // &&
    T_BG,        // &
    T_REDIR_IN,
    T_REDIR_OUT,
    T_REDIR_APPEND,
    T_REDIR_HEREDOC
} t_token_type;

typedef enum e_redir_type {
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
    REDIR_HEREDOC
} t_redir_type;

typedef struct s_token {
    t_token_type type;
    char *value;
    struct s_token *next;
    int index;
} t_token;


typedef struct s_redir {
    char *filename;
<<<<<<< Updated upstream
    t_redir_type type;
=======
    t_redir_type type; 
    int *pipe_forhdc;
>>>>>>> Stashed changes
} t_redir;

typedef struct s_command {
   // char    *name;
    char    **arguments;
    t_redir **redir_in;
    t_redir **redir_out;
    int     redir_in_count;
    int     redir_out_count;
    int     arg_count;
    char    *command;
    struct s_command *next;
} t_command;

typedef struct s_cmd_builder {
    t_command   *cmd;
    t_list      *args;
    t_list      *redir_in;
    t_list      *redir_out;
} t_cmd_builder;





// ANEZKAS_PART

//builtin fce
int what_builtin(t_command *cmd);
int run_pwd(void);
int run_echo(char **string);
int run_cd(char *path, env_t *env); //todo home
int run_env(char **envp);
int run_exit(void); //todo s ciselkami
int run_export(env_t *env, char *arguments);
int run_unset(env_t *env, char *arguments);
env_t *adding_env(env_t *cmd, char **envp);
//utils
int saving_env(char ***env, char *envp[]);
int copy_string(char **env, char *orig_env);
int find_start(char *envp[], char *arguments);
int counting_envlen(char **envp);
char  **put_envp(char **old_envp, char *new_arg);
int get_order(char **envp);
char *find_variable(char *arguments);
char **put_unset(char **old_env, int unset);
int unset_variable(char *envp, char *variable, int i);
void	ft_putstr_fd(char *s, int fd);
char *find_envar(env_t *env, char *find);
//redirect
int redirecting_in(char *str);
int redirecting_out(char *str);
int appending(char *str);
//nonbuiltins
int executing(char *str, char *evnp[]);
//libft_later
int	ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
int	ft_numstrings(const char *s, int c);
unsigned int	findend(const char *s, int c, int i);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);


// SISIS_PART

//tokenizing.c
void append_token(t_token **head, t_token *new_tok);
bool is_operator_start(char c);
size_t skip_spaces(const char *input, size_t i);
void print_tokens(t_token *head);
t_token *tokenize(const char *input);
//parser_handle_token.c
void handle_token(t_token *tok, t_cmd_builder *b);
void handle_in_redir(t_token *tok, t_cmd_builder *b);
void handle_out_redir(t_token *tok, t_cmd_builder *b);
//free.c
void free_tokens(t_token *head);
void free_redir_array(t_redir **arr, int count);
void free_cmd(t_command *cmd);
void free_array(char **arr);
void free_argv(char **argv);
//parse_token.c
t_token_type get_token_type_len(const char *str, size_t len);
size_t parse_quoted(const char *input, size_t i, t_token **tokens);
size_t parse_operator(const char *input, size_t i, t_token **tokens);
size_t parse_word(const char *input, size_t i, t_token **tokens);
t_redir_type get_redir_type(const char *str, size_t len);
//parse_tok_loop.c
bool parse_tokens(t_token *tok, t_command **out);
t_redir **list_to_array(t_list *list, int *count);
//parse_pipes.c
void find_segment_end(t_token **end, t_token *tokens);
bool init_commands(t_command **head, t_token *tokens);
//process.c
const char *token_type_to_string(t_token_type type);
t_token *argv_to_token_list(int argc, char **argv);

void print_list(char **arr, const char *label);
void print_args(t_command *cmd);
void print_command(t_command *cmd, int index);

void print_redirs(t_redir **redirs, int count, const char *label);
int is_exit_input(const char *line, ssize_t n);
t_command *run_shell_line(char *line);

bool is_redir_token(t_token *tok);

t_token *new_token(const char *str, size_t len, t_token_type type, int pos);
t_redir *new_redir(t_token *tok, t_redir_type type);
void add_redir_token(t_token *tok, t_cmd_builder *b);
void list_add_back(t_list **list, void *content);
bool init_cmd_builder(t_cmd_builder *b, t_command **out);
bool process_tokens(t_token *tok, t_cmd_builder *b);
void finalize_cmd_builder(t_cmd_builder *b, t_command **out);
bool parse_tokens(t_token *tok, t_command **out);

#endif