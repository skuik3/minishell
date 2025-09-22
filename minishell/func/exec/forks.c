/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:56:25 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/22 09:53:51 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int first_multiple(t_biggie *bigs) //in child process
{
    if (bigs->cmd->redir_in != NULL || bigs->cmd->redir_out != NULL)
    {
        if (check_redirect(bigs->cmd) == 1)
        {
            perror("");
            free_big(bigs);
            exit(1);
        }
    }
    if (bigs->cmd->redir_out == NULL)
    {
        if (dup2(bigs->pipe_cmd->pipe[1], STDOUT_FILENO) == -1)   
        {
            perror("");
            return (1);
        }
    }
    close(bigs->pipe_cmd->pipe[0]);
    close(bigs->pipe_cmd->pipe[1]);
    if (is_builtint(bigs->cmd->command) == 0)
        bigs->exit_status = what_builtin(bigs);
    else if (is_builtint(bigs->cmd->command) == 1)
        bigs->exit_status = executing(bigs->cmd);
    return (bigs->exit_status);
}

int other_multiple(t_biggie *bigs)
{
    if (bigs->cmd->redir_in != NULL || bigs->cmd->redir_out != NULL)
    {
        if (check_redirect(bigs->cmd) == 1)
        {
            perror("");
            free_big(bigs);
            exit(1);
        }
    }
    if (bigs->cmd->redir_in == NULL)
    {
        if (dup2(bigs->pipe_cmd->pipe[0], STDIN_FILENO) == -1)
        {
            perror("");
            return (1);
        }
    }
    close(bigs->pipe_cmd->pipe[0]); 
    if (bigs->cmd->redir_out == NULL)
    {
        if (dup2(bigs->pipe_cmd->next->pipe[1], STDOUT_FILENO) == -1)
        {
            perror("");
            return (1);
        }
    }
    close(bigs->pipe_cmd->next->pipe[0]);
    close(bigs->pipe_cmd->next->pipe[1]);
    if (is_builtint(bigs->cmd->command) == 0)
        bigs->exit_status = what_builtin(bigs);
    else if (is_builtint(bigs->cmd->command) == 1)
        bigs->exit_status = executing(bigs->cmd);
    return (bigs->exit_status);  
}

int last_multiple(t_biggie *bigs)
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
        if (bigs->cmd->redir_in != NULL || bigs->cmd->redir_out != NULL)
        {
            if (check_redirect(bigs->cmd) == 1)
            {
                perror("");
                free_big(bigs);
                exit(1);
            }
        }
        if (bigs->cmd->redir_in == NULL)
        {
            if (dup2(bigs->pipe_cmd->pipe[0], STDIN_FILENO) == -1)
            {
                perror("");
                exit (1);
            }
        }
        close(bigs->pipe_cmd->pipe[0]);
        if (is_builtint(bigs->cmd->command) == 0)
            status = what_builtin(bigs);
        else if (is_builtint(bigs->cmd->command) == 1)
            status = executing(bigs->cmd);
        free_big(bigs);
        exit(status);
    }
    close(bigs->pipe_cmd->pipe[0]);
    while (wait(&bigs->exit_status) != -1)
        ;
    bigs->exit_status = WEXITSTATUS(bigs->exit_status);
    if (bigs->exit_status == 2)
        bigs->exit_status = 130;
    return (bigs->exit_status);
}
