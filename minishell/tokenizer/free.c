/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:54:48 by skuik             #+#    #+#             */
/*   Updated: 2025/07/21 17:02:21 by anezkahavra      ###   ########.fr       */
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

void free_pipeline(t_pipeline *pipe)
{
    while (pipe)
    {
        t_pipeline *next = pipe->next;
        t_command *cmd = pipe->cmd;
        free(cmd->command);
        free_array(cmd->arguments);
        free_array(cmd->redir_in);
        free_array(cmd->redir_out);
        free(cmd->heredoc);
        free(cmd->append);
        free(cmd);
        free(pipe);
        pipe = next;
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
