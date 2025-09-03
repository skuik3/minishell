/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:56:25 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/03 11:29:25 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int first_multiple(t_command *cmd, t_pipe *pipe_cmd) //in child process
{
    int status;

    if (cmd->redir_in != NULL || cmd->redir_out != NULL)
    {
        if (status = check_redirect(cmd) == 1)
            return (1);
    }
    if (cmd->redir_out == NULL)
    {
        if (dup2(pipe_cmd->pipe[1], STDOUT_FILENO) == -1)   
        {
            perror("");
            return (1);
        }
    }
    close(pipe_cmd->pipe[0]);
    close(pipe_cmd->pipe[1]);
    if (is_builtint(cmd->command) == 0)
        status = what_builtin(cmd);
    else if (is_builtint(cmd->command) == 1)
        status = executing(cmd);
    return (status);
}

int other_multiple(t_command *cmd, t_pipe *pipe_cmd)
{
    int status;

    if (cmd->redir_in != NULL || cmd->redir_out != NULL)
    {
        if (status = check_redirect(cmd) == 1)
            return (1);
    }
    if (cmd->redir_in == NULL)
    {
        if (dup2(pipe_cmd->pipe[0], STDIN_FILENO) == -1)
        {
            perror("");
            return (1);
        }
    }
    close(pipe_cmd->pipe[0]); 
    if (cmd->redir_out == NULL)
    {
        if (dup2(pipe_cmd->next->pipe[1], STDOUT_FILENO) == -1)
        {
            perror("");
            return (1);
        }
    }
    close(pipe_cmd->next->pipe[0]);
    close(pipe_cmd->next->pipe[1]);
    if (is_builtint(cmd->command) == 0)
        status = what_builtin(cmd);
    else if (is_builtint(cmd->command) == 1)
        status = executing(cmd);
    return (status);  
}

int last_multiple(t_command *cmd, t_pipe *pipe_cmd)
{
    int pid;
    int status;
    
    pid = fork();
    if (pid < -1)
    {
        perror("");
        return (1);
    }
    else if (pid == 0)
    {
        if (cmd->redir_in != NULL || cmd->redir_out != NULL)
        {
            if (status = check_redirect(cmd) == 1)
                return (1);
        }
        if (cmd->redir_in == NULL)
        {
            if (dup2(pipe_cmd->pipe[0], STDIN_FILENO) == -1)
            {
                perror("");
                exit (1); //return prv
            }
        }
        close(pipe_cmd->pipe[0]);
        if (is_builtint(cmd->command) == 0)
            status = what_builtin(cmd);
        else if (is_builtint(cmd->command) == 1)
            status = executing(cmd);
        exit(0);
    }
    close(pipe_cmd->pipe[0]);
    while (wait(&status) != -1)
        ;
    return (status);
}
