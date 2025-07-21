/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:59:49 by skuik             #+#    #+#             */
/*   Updated: 2025/07/21 00:15:41 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void find_segment_end(t_token **end, t_token *tokens)
{
    *end = NULL;
    
    while (tokens && tokens->type != T_PIPE)
    {
        *end = tokens;
        tokens = tokens->next;
    }
}

void init_pipeline(t_pipeline **head, t_token *tokens)
{
    t_pipeline *tail = NULL;
    t_command *cmd = NULL;

    while (tokens)
    {
        t_token *segment = tokens, *end = NULL;
        find_segment_end(&end, tokens);
        if (end && end->next)
        {
            tokens = end->next->next;
            end->next = NULL;
        }
        else
            tokens = NULL;
        parse_tokens(segment, &cmd);
        t_pipeline *node = malloc(sizeof(t_pipeline));
        if (!node)
            return;
        node->cmd = cmd;
        node->next = NULL;
        if (!(*head))
            *head = node;
        else
            tail->next = node;
        tail = node;
    }
}
