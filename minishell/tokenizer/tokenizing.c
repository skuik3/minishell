/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:42:30 by skuik             #+#    #+#             */
/*   Updated: 2025/07/21 14:03:05 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void append_token(t_token **head, t_token *new_tok)
{
    if (!*head)
    {
        *head = new_tok;
        return;
    }
    t_token *cur = *head;
    while (cur->next)
        cur = cur->next;
    cur->next = new_tok;
}

bool is_operator_start(char c)
{
    return (c == '>' || c == '<' || c == '|' || c == '&' || c == ';');
}

size_t skip_spaces(const char *input, size_t i)
{
    while (input[i] && isspace(input[i]))
        i++;
    return (i);
}

void print_tokens(t_token *head)
{
    int i;
    
    i = 0;
    while (head)
    {
        printf("Token[%d]: %-10s\t(Type: %d)\n", i++, head->value, head->type);
        head = head->next;
    }
}

t_token *tokenize(const char *input)
{
    t_token *tokens = NULL;
    size_t i = 0;

    while (input[i])
    {
        i = skip_spaces(input, i);
        if (!input[i])
            break;
        if (input[i] == '"' || input[i] == '\'')
            i = parse_quoted(input, i, &tokens);
        else if (is_operator_start(input[i]))
            i = parse_operator(input, i, &tokens);
        else
            i = parse_word(input, i, &tokens);
    }
    return (tokens);
}
