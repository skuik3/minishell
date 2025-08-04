/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:56:25 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/08/04 12:21:14 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int first_multiple(t_command *cmd, t_pipe *pipe_cmd) //in child process
{
    if (cmd->redir_in != NULL || cmd->redir_out != NULL)
        check_redirect(cmd);
    if (cmd->redir_out == NULL)
    {
        if (dup2(pipe_cmd->pipe[1], STDOUT_FILENO) == -1)   
            return (ft_putstr_fd(ERR_DUP, STDERR_FILENO), 1);
    }
    close(pipe_cmd->pipe[0]);
    close(pipe_cmd->pipe[1]); //maybe not necessary, since dup2 should close it automatically
    if (is_builtint(cmd->command) == 0)
        what_builtin(cmd);
    else if (is_builtint(cmd->command) == 1)
        executing(cmd);
    // close(pipe_cmd->pipe[1]); //maybe not
    return (0);
}

int other_multiple(t_command *cmd, t_pipe *pipe_cmd)
{
    if (dup2(pipe_cmd->pipe[0], STDIN_FILENO) == -1)
        return (ft_putstr_fd(ERR_DUP, STDERR_FILENO), 1);
    close(pipe_cmd->pipe[0]); 
    if (cmd->redir_in != NULL || cmd->redir_out != NULL)
        check_redirect(cmd);
    if (cmd->redir_out == NULL)
    {
        if (dup2(pipe_cmd->next->pipe[1], STDOUT_FILENO) == -1)
            return (ft_putstr_fd(ERR_DUP, STDERR_FILENO), 1);
    }
    close(pipe_cmd->next->pipe[0]);
    close(pipe_cmd->next->pipe[1]);
    if (is_builtint(cmd->command) == 0)
        what_builtin(cmd);
    else if (is_builtint(cmd->command) == 1)
        executing(cmd);
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
        if (dup2(pipe_cmd->pipe[0], STDIN_FILENO) == -1)
            return (ft_putstr_fd(ERR_DUP, STDERR_FILENO), 1);
        close(pipe_cmd->pipe[0]);
        if (cmd->redir_in != NULL || cmd->redir_out != NULL)
            check_redirect(cmd);
        if (is_builtint(cmd->command) == 0)
            what_builtin(cmd);
        else if (is_builtint(cmd->command) == 1)
            executing(cmd);
        exit(0);
    }
    close(pipe_cmd->pipe[0]);
    while (wait(&status) != -1)
        ;
    return (0);
}
