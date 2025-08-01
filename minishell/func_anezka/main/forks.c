/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:56:25 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/08/01 10:54:44 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int first_multiple(t_command *cmd, t_pipe *pipe_cmd) //in child process
{
    close(pipe_cmd->pipe[0]); 
    if (dup2(pipe_cmd->pipe[1], STDOUT_FILENO) == -1)   
        return (ft_putstr_fd(ERR_DUP, STDERR_FILENO), 1);
    if (is_builtint(cmd->command) == 0)
        what_builtin(cmd);
    else if (is_builtint(cmd->command) == 1)
        executing(cmd);
    close(pipe_cmd->pipe[1]); //maybe not
    return (0);
}

int other_multiple(t_command *cmd, t_pipe *pipe_cmd)
{
    close(pipe_cmd->pipe[1]);
    pipe_cmd = pipe_cmd->next;
    if (dup2(pipe_cmd->pipe[0], STDOUT_FILENO) == -1)
        return (ft_putstr_fd(ERR_DUP, STDERR_FILENO), 1);
    if (is_builtint(cmd->command) == 0)
        what_builtin(cmd);
    else if (is_builtint(cmd->command) == 1)
        executing(cmd);
    // close(pipe_cmd->pipe[1]); //maybe not
    return (0);  
}

int last_multiple(t_command *cmd, t_pipe *pipe_cmd)
{
    int pid;
    int status;

    pid = fork();
    if (pid < -1)
            return (ft_putstr_fd(ERR_FORK, STDERR_FILENO), 1);
    else if (pid == 0)
    {
        close(pipe_cmd->pipe[1]);
        if (is_builtint(cmd->command) == 0)
            what_builtin(cmd);
        else if (is_builtint(cmd->command) == 1)
            executing(cmd);
    }
    else if (pid > 0)
        waitpid(pid, &status, 0);
    return (0);
}