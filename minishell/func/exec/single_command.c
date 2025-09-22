/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:45:02 by anezka            #+#    #+#             */
/*   Updated: 2025/09/22 14:39:40 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_before_single(t_biggie *bigs)
{
    bigs->exit_status = check_heredoc(bigs);
    if (bigs->exit_status == 1)
    {
        perror("");
        return (1);
    }
    if (bigs->exit_status == SIGINT)
        return (130);
    if (bigs->cmd->redir_in != NULL || bigs->cmd->redir_out != NULL)
    {
        if (check_redirect(bigs->cmd) == 1)
        {
            perror("");
            return (1); 
        }
    }
    return (0);
}

int single_nonbuiltin(t_biggie *bigs)
{
    int pid;
    int status;

    signal(SIGINT, handle_signal_child);
    pid = fork();
    if (pid < -1)
    {
        perror("");
        return (1);
    }
    else if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        status = executing(bigs->cmd);
        free_big(bigs);
        exit(status);
    }
    waitpid(pid, &bigs->exit_status, 0);
    bigs->exit_status = WEXITSTATUS(bigs->exit_status);
    if (bigs->exit_status == 2 || g_signal == SIGINT)
        bigs->exit_status = 130;
    return (bigs->exit_status);
}

//maybe check after changing bigs
void close_herepipe(t_command *cmd) 
{
    int i = 0;
    while (cmd->redir_in[i + 1] != NULL)
        i++;
    if (cmd->redir_in[i]->type == REDIR_HEREDOC)
        close(cmd->redir_in[i]->pipe_forhdc[0]);    
}

int restore_fd(int stdout_orig, int stdin_orig)
{
    if (dup2(stdout_orig, STDOUT_FILENO) == -1 
        || dup2(stdin_orig, STDIN_FILENO) == -1)
        {
            perror("");
            return (1);
        }
    close(stdout_orig);
    close(stdin_orig);
    return (0);
}

int single_command(t_biggie *bigs)
{
    int stdout_orig;
    int stdin_orig;

    stdout_orig = dup(STDOUT_FILENO);
    stdin_orig = dup(STDIN_FILENO);
    if (stdout_orig == -1 || stdin_orig == -1)
    {
        perror("");
        return (1);
    }
    bigs->exit_status = check_before_single(bigs);
    if (bigs->exit_status != 0)
        return (bigs->exit_status);
    if (is_builtint(bigs->cmd->command) == 0)
        bigs->exit_status = what_builtin(bigs);
    else
        bigs->exit_status = single_nonbuiltin(bigs);
    if (bigs->cmd->redir_in != NULL)
        close_herepipe(bigs->cmd);
    restore_fd(stdout_orig, stdin_orig);
    return (bigs->exit_status);
}
