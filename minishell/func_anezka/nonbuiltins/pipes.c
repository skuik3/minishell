/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:57:39 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/31 22:44:31 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int counting_pipes(t_command *cmd)
{
    int count;

    count = 0;
    while (cmd->next != NULL)
    {
        cmd = cmd->next;
        count++;
    }
    return (count - 1);
}

t_pipe *prepare_pipes(t_command *cmd)
{
    int pipe_count;
    t_pipe *pipe_cmd;

    pipe_count = counting_pipes(cmd);
    if (pipe_count > 0)
    {
        pipe_cmd = malloc(sizeof(t_pipe) * (pipe_count + 1));
        if (pipe_cmd == NULL)
            return(ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), NULL);
        while(pipe_cmd->next != NULL)
        {
            pipe_cmd->pipe = malloc(sizeof(int) * (2 + 1));
            if (pipe_cmd->pipe == NULL)
                return(ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), NULL);
            if (pipe(pipe_cmd->pipe) == -1)
                return (ft_putstr_fd(ERR_PIPE, STDERR_FILENO), NULL);
            pipe_cmd = pipe_cmd->next;
        }
    }
    return(pipe_cmd);
}