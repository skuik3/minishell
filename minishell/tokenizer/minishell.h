/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:01:00 by skuik             #+#    #+#             */
/*   Updated: 2025/07/07 13:19:55 by skuik            ###   ########.fr       */
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

//["echo", "hello", ">", "lol"]
struct input {
    char *name;       // echo
    char **args;      // ["echo", "hello", NULL]
    char *file_out;   // "lol"
    bool redirect_out; // true
    bool run_in_background; // if & was used
    bool is_pipe; // if followed by |
};


typedef struct s_token {
    char            *value;   //the whole str "echo", "-n", ">", "file.txt"
    t_token_type    type;     //what is the tokens type
    struct s_token  *next;    //linked list

}       t_token;

static t_token_type get_token_type(const char *str) {
    if (strcmp(str, ">>") == 0) return T_APPEND;
    if (strcmp(str, ">") == 0) return T_REDIR_OUT;
    if (strcmp(str, "<<") == 0) return T_HEREDOC;
    if (strcmp(str, "<") == 0) return T_REDIR_IN;
    if (strcmp(str, "||") == 0) return T_OR;
    if (strcmp(str, "&&") == 0) return T_AND;
    if (strcmp(str, "|") == 0) return T_PIPE;
    if (strcmp(str, "&") == 0) return T_BG;
    if (strcmp(str, ";") == 0) return T_END;
    return T_WORD;
}

static t_token *new_token(const char *start, size_t len, t_token_type type) {
    t_token *tok = malloc(sizeof(t_token));
    tok->value = strndup(start, len);
    tok->type = type;
    tok->next = NULL;
    return tok;
}

static const char *token_type_to_string(t_token_type type) {
    switch (type) {
        case T_WORD:       return "WORD";
        case T_PIPE:       return "PIPE";
        case T_REDIR_IN:   return "REDIR_IN";
        case T_REDIR_OUT:  return "REDIR_OUT";
        case T_APPEND:     return "APPEND";
        case T_HEREDOC:    return "HEREDOC";
        case T_END:        return "END";
        case T_OR:         return "OR";
        case T_AND:        return "AND";
        case T_BG:         return "BG";
        default:           return "UNKNOWN";
    }
}

void skip_leading_whitespace(char **str);

