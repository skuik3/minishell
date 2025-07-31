/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:56:25 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/31 23:43:53 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int first_multiple(t_command *cmd, t_pipe *pipe_cmd) //in child process
{
    if (dup2(pipe_cmd->pipe[1], STDOUT_FILENO) == -1)   
        return (ft_putstr_fd(ERR_DUP, STDERR_FILENO), 1);
    close(pipe_cmd->pipe[0]); 
    if ()

}