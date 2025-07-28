/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:38:30 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/28 13:59:57 by anezkahavra      ###   ########.fr       */
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
#define ERR_MALLOC  "Malloc failure\n"
#define ERR_ARG     "Not enough arguments\n"
#define ERR_FILE    "Error opening/creating a file\n"
#define ERR_FORK    "Error forking\n"
#define ERR_BC      "Error\n" 

//structs
typedef struct environment_variables
{
    char **start;
    char **mod;
} env_t;

typedef enum e_token_type {
    T_WORD,       //hello
    T_PIPE,       // |
    T_REDIR_IN,   // <
    T_REDIR_OUT,  // >
    T_APPEND,     // >>
    T_HEREDOC,    // <<
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

typedef struct s_command {
    char *command;
    char **arguments;
    char **redir_in;
    char **redir_out;
    char *heredoc;
    char *append;
    struct s_command *next;
    env_t *envar;  // add aneskas env
} t_command;

//TEST VERSION
// Your command structure (unchanged from previous version)
// typedef struct s_command {
//     char *command;         // name of the command
//     char **arguments;      // all arguments needed for running the command or NULL
//     char **redir_in;       // redirecting in
//     char **redir_out;      //redirecting out
//     char *heredoc;         // heredoc delimiter
//     char *append;          // appending mode
//     struct s_command *next; // pointer to a next struct if pipes present
//     env_t *envar;          // environment variables
// } t_command;

// size_t count_env_vars(char **env);
// env_t *create_environment(char *envp[]);
// int modify_environment(env_t *env, const char *key, const char *value);
// void free_environment(env_t *env);
// t_command *parse_input(const char *line);
// void free_command(t_command *cmd);
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

// ANEZKAS_PART

//builtin fce
int what_builtin(t_command *cmd);
int run_pwd(void);
int run_echo(char **string);
int run_cd(char *path, env_t *env); //todo home
int run_env(char **envp);
int run_exit(void); //todo s ciselkami
int run_export(env_t *envp, char **arguments);
int run_unset(env_t *envp, char **arguments);
env_t *adding_env(t_command *cmd, char **envp);
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
char *find_path(env_t *env, char *find_var);
char *adding_variable(char *argument);
//redirect
int redirecting_in(t_command *cmd);
int redirecting_out(char *str);
int appending(t_command *cmd);
//nonbuiltins
int executing(t_command *cmd);
int is_path(char *command);
char *command_path(t_command *cmd);
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
void free_pipeline(t_pipeline *pipe);
void free_array(char **arr);
void free_argv(char **argv);
//parse_token.c
t_token *new_token(const char *start, size_t len, t_token_type type);
t_token_type get_token_type_len(const char *str, size_t len);
size_t parse_quoted(const char *input, size_t i, t_token **tokens);
size_t parse_operator(const char *input, size_t i, t_token **tokens);
size_t parse_word(const char *input, size_t i, t_token **tokens);
//parse_tok_loop.c
void parse_tokens(t_token *tok, t_command **out);
void parse_token_loop(t_token *tok, t_cmd_builder *b);
char **list_to_array(t_list *list);
//parse_pipes.c
void find_segment_end(t_token **end, t_token *tokens);
void init_pipeline(t_pipeline **head, t_token *tokens);
//process.c
const char *token_type_to_string(t_token_type type);
t_token *argv_to_token_list(int argc, char **argv);

void print_list(char **arr, const char *label);
void print_command(t_command *cmd, int index);
void print_pipeline(t_pipeline *pipe);
int is_exit_input(const char *line, ssize_t n);
void run_shell_line(char *line);

#endif