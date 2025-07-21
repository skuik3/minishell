/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:59:57 by skuik             #+#    #+#             */
/*   Updated: 2025/07/21 17:02:47 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *new_token(const char *start, size_t len, t_token_type type)
{
    t_token *tok = malloc(sizeof(t_token));
    tok->value = strndup(start, len);
    tok->type = type;
    tok->next = NULL;
    return (tok);
}

t_token_type get_token_type_len(const char *str, size_t len)
{
    if (len == 2)
    {
        if (strncmp(str, ">>", 2) == 0) return T_APPEND;
        if (strncmp(str, "<<", 2) == 0) return T_HEREDOC;
        if (strncmp(str, "||", 2) == 0) return T_OR;
        if (strncmp(str, "&&", 2) == 0) return T_AND;
    }
    else if (len == 1)
    {
        if (*str == '>') return T_REDIR_OUT;
        if (*str == '<') return T_REDIR_IN;
        if (*str == '|') return T_PIPE;
        if (*str == '&') return T_BG;
        if (*str == ';') return T_END;
    }
    return (T_WORD);
}

size_t parse_quoted(const char *input, size_t i, t_token **tokens)
{
    char quote = input[i++];
    size_t start = i;
    
    while (input[i] && input[i] != quote)
        i++;
    if (input[i] == quote)
        append_token(tokens, new_token(&input[start], i - start, T_WORD));
    else
        append_token(tokens, new_token(&input[start], i - start, T_WORD));
    if (input[i] == quote)
        return (i + 1);
    else
        return (i);
}

size_t parse_operator(const char *input, size_t i, t_token **tokens)
{
    size_t start = i;
    t_token_type type;

    if ((input[i] == '>' || input[i] == '<' || input[i] == '|' || input[i] == '&')
        && input[i + 1] == input[i])
    {
        type = get_token_type_len(&input[i], 2);
        i += 2;
    }
    else
    {
        type = get_token_type_len(&input[i], 1);
        i += 1;
    }
    append_token(tokens, new_token(&input[start], i - start, type));
    return (i);
}

size_t parse_word(const char *input, size_t i, t_token **tokens)
{
    size_t start = i;
    while (input[i] && !isspace(input[i]) && !is_operator_start(input[i]))
        i++;
    append_token(tokens, new_token(&input[start], i - start, T_WORD));
    return (i);
}