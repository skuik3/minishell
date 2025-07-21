/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:01:00 by skuik             #+#    #+#             */
/*   Updated: 2025/07/21 13:18:10 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE

#include "helper_funcs/libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 256

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
    //env_t *env_ptr;  // add aneskas env
} t_command;

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