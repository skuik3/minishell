/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:54:48 by skuik             #+#    #+#             */
/*   Updated: 2025/07/23 18:59:40 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_tokens(t_token *head)
{
    while (head)
    {
        t_token *tmp = head;
        head = head->next;
        free(tmp->value);
        free(tmp);
    }
}

void free_cmd(t_command *cmd)
{
    while (cmd)
    {
        t_command *next = cmd->next;

        free(cmd->command);
        free_array(cmd->arguments);
        free_array(cmd->redir_in);
        free_array(cmd->redir_out);
        free(cmd->heredoc);
        free(cmd->append);

        free(cmd);
        cmd = next;
    }
}

void free_array(char **arr)
{
    if (!arr)
        return;
    char **temp = arr;
    while (*temp)
    {
        free(*temp);
        temp++;
    }
    free(arr);
}

void free_argv(char **argv)
{
    if (argv == NULL)
        return;
    char **temp = argv;
    while (*temp)
    {
        free(*temp);
        temp++;
    }
    free(argv);
}
