/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:38:30 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/18 19:51:57 by anezka           ###   ########.fr       */
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
#include <signal.h>
#include <sys/wait.h>
// #include "get_next_line/get_next_line.h"
#include <sys/ioctl.h>

extern int g_signal;

#include "helper_funcs/libft.h"

#define _GNU_SOURCE
#define MAX_TOKENS 256

//for readability
#define SHELL_DEFAULT 00644
#define ERR_MALLOC  "Malloc failure\n"
#define ERR_ARG     "Not enough arguments\n"
#define ERR_FILE    "Error opening/creating a file\n"
#define ERR_NOTFILE "No such file or directory\n"
#define ERR_FORK    "Error forking\n"
#define ERR_BC      "Error\n" 
#define ERR_PIPE    "Error creating a pipe\n"
#define ERR_DUP     "Error duplicating\n"
#define ERR_READ    "Error reading\n"
#define ERR_EXEC    "Error executing file\n"

#define INVALID_PAR "Invalid parameter name\n"


//structs
typedef struct environment_variables
{
    char **start;
    char **mod;
} env_t;

typedef struct pipe
{
    int *pipe;
    struct pipe *next;
}   t_pipe;


typedef enum e_token_type {
    T_WORD,       //hello
    T_PIPE,       // |
    T_REDIR_IN,   // <
    T_REDIR_OUT,  // >
    T_REDIR_APPEND,     // >>
    T_REDIR_HEREDOC,    // <<
    T_END,         // end of str
    T_OR,        // ||
    T_AND,       // &&
    T_BG,        // &
}   t_token_type;

typedef struct s_token {
    char *value;
    t_token_type type;
    struct s_token *next;
} t_token;

// typedef struct s_command {
//     char *command;
//     int is_first;
//     char **arguments;
//     char **redir_in;
//     char **redir_out;
//     char *heredoc;
//     char *append;
//     struct s_command *next;
//     env_t *envar;  // add aneskas env
// } t_command;


//TEST VERSION
typedef enum e_redir_type {
    REDIR_IN,     // <
    REDIR_OUT,    // >
    REDIR_APPEND, // >>
    REDIR_HEREDOC // <<
} t_redir_type;

typedef struct s_redir {
    char *filename;
    t_redir_type type; 
    int *pipe_forhdc;
    int position; // position in the original command
} t_redir;

typedef struct s_command {
    char *command;
    int is_first;
    char **arguments;
    t_redir **redir_in;      // array of pointers to input redirections (< and <<)
    int redir_in_count;
    t_redir **redir_out;     // array of pointers to output redirections (> and >>)
    int redir_out_count;
    // char *heredoc;
    // char *append;
    struct s_command *next;
    env_t *envar;  // add aneskas env
} t_command;
//END OF TEST VERSION   

typedef struct s_pipeline {
    t_command           *cmd;
    struct s_pipeline   *next;
} t_pipeline;


typedef struct s_cmd_builder {
    t_command   *cmd;
    t_list      *args;
    t_list      *redir_in;
    t_list      *redir_out;
} t_cmd_builder;

typedef struct s_node
{
    void *content;
    struct s_list *next;
} t_node;

typedef struct s_biggiest_struct
{
    t_command *cmd;
    env_t *env;
    t_pipe  *pipe_cmd;
    int exit_status;
    int exit_bef;
}   t_biggie;

// ANEZKAS_PART
void free_big(t_biggie *bigs);
void clean_big(t_biggie *bigs);
void free_arguments(char **arguments);
//main_execution
int what_builtin(t_biggie *bigs);
env_t *adding_env(t_command *cmd, char **envp);
int command_execution(t_biggie *bigs);
int single_command(t_biggie *bigs);
int multiple_commands(t_biggie *bigs);
int last_multiple(t_biggie *bigs);
int other_multiple(t_biggie *bigs);
int first_multiple(t_biggie *bigs);
t_biggie *setting_big(void);
void close_herepipe(t_command *cmd);
int check_before_single(t_biggie *bigs);
//utils for main_execution
int saving_env(char ***env, char *envp[]);
int is_builtint(char *command);
//signals
void handle_signal_main(int signal);
void handle_signal_child(int signal);
void handle_signal_heredoc(int signal);
//builtin fce
int run_pwd(void);
int run_echo(char **string);
int run_cd(char **path, env_t *env); //todo home
int run_env(t_biggie *bigs);
int run_exit(t_biggie *bigs); //todo s ciselkami
int run_export(t_biggie *bigs);
int run_unset(env_t *envp, char **arguments);
//utils for builtin fce
int copy_string(char **env, char *orig_env);
int find_start(char *envp[], char *arguments);
int counting_envlen(char **envp);
char  **put_envp(char **old_envp, char *new_arg);
int get_order(char **envp);
char *find_variable(char *arguments);
char **put_unset(char **old_env, int unset);
int unset_variable(char *envp, char *variable, int i);
char *find_envar(env_t *env, char *find);
char *find_path(env_t *env, char *find_var);
char *adding_variable(char *argument);
int variable_present(char *variable, env_t *envp);
char **exchange_values(char **envp, char *exchange);
char **prepare_unset(char *argument);
int value_present(char *argument);
char **adding_command(t_command *cmd);
int just_nb(char *nb);
int unset_value(env_t *envp, char *argument);
int number_exit(char *args);
int check_variable(char *variable);
int unseting(env_t *envp, char *arguments);
int find_unset(char *arguments, env_t *envp);
int unset_position(char *envp, char *variable, int i);
int export_argument(env_t *envp, char *argument);
int inner_check(char *envp[], int i);
//pipes
int counting_pipes(t_command *cmd);
t_pipe *prepare_pipes(t_command *cmd);
t_pipe *creating_first_pipe(void);
t_pipe *adding_pipe(t_pipe *pipe_cmd);
//redirect
int redirect_out(t_command *cmd);
int last_redirect_out(t_redir *last);
int appending(t_redir *append);
int redirecting_out(t_redir *redirout);
int check_redirect(t_command *cmd);
int redirecting_in(t_redir *redirin);
int last_redirect_in(t_redir *last);
int redirect_in(t_command *cmd);
int heredoc_present(t_redir **redir);
int check_heredoc (t_command *cmd);
int do_heredoc(t_command *cmd);
char *get_line_heredoc(t_redir *last);
int last_heredoc(t_redir *last);
int redirecting_heredoc(t_redir *heredoc);
int where_last_heredoc(t_command *cmd, int redi);
int last_heredoc_multiple(t_redir *last);
int do_heredoc_multiple(t_command *cmd);
//nonbuiltins
int executing(t_command *cmd);
//nonbuiltins utils
int is_path(char *command);
char *command_path(t_command *cmd);
//libft_later
int	ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
int	ft_numstrings(const char *s, int c);
unsigned int	findend(const char *s, int c, int i);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	ft_putstr_fd(char *s, int fd);
int	ft_isalnum(int c);
int	ft_isalpha(int c);

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
void free_commands(t_command *cmd);
void free_array(char **arr);
void free_argv(char **argv);
//parse_token.c
t_token *new_token(const char *start, size_t len, t_token_type type);
t_redir_type get_redir_type(const char *str, size_t len);
t_token_type get_token_type_len(const char *str, size_t len);
size_t parse_quoted(const char *input, size_t i, t_token **tokens);
size_t parse_operator(const char *input, size_t i, t_token **tokens);
size_t parse_word(const char *input, size_t i, t_token **tokens);
//parse_tok_loop.c
bool parse_tokens(t_token *tok, t_command **out);
void list_add_back(t_list **list, void *content);
char **list_to_array(t_list *list);
//parse_pipes.c
void find_segment_end(t_token **end, t_token *tokens);
bool init_commands(t_command **head, t_token *tokens);
//process.c
const char *token_type_to_string(t_token_type type);
t_token *argv_to_token_list(int argc, char **argv);

void print_list(char **arr, const char *label);
void print_command(t_command *cmd, int index);
void print_commands(t_command *cmd);
int is_exit_input(const char *line, ssize_t n);
t_command *run_shell_line(char *line);

#endif