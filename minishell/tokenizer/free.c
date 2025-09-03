/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:54:48 by skuik             #+#    #+#             */
/*   Updated: 2025/09/03 15:59:32 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_tokens(t_token *head)
{
    t_token *tmp;

    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp->value);
        free(tmp);
    }
}

void free_redir_array(t_redir **arr, int count)
{
    if (count <= 0 || !arr)
        return;

    t_redir **current = arr;
    while (count--)
    {
        if (*current)
        {
            free((*current)->filename);
            free(*current);
        }
        current++;
    }
    free(arr);
}

void free_array(char **arr)
{
    if (!arr)
        return;

    char **current = arr;
    while (*current)
    {
        free(*current);
        current++;
    }
    free(arr);
}

void free_cmd(t_command *cmd)
{
    t_command *next;

    while (cmd)
    {
        next = cmd->next;
        free_array(cmd->args);
        free_redir_array(cmd->redirs, cmd->redir_count);
        free(cmd);
        cmd = next;
    }
}

void free_cmd_builder(t_cmd_builder *builder)
{
    if (!builder)
        return;

    free_cmd(builder->cmd);
    // free_list(builder->args);
    // free_list(builder->redir_in);
    // free_list(builder->redir_out);
    free(builder);
}

