/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/19 23:38:19 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_before_multiple(t_biggie *bigs)
{
    bigs->exit_status = check_heredoc(bigs);
    if (bigs->exit_status == 1)
    {
        perror("");
        return (1);
    }
    if (bigs->exit_status == SIGINT)
        return (130);
    return (0);
}
//check the exiting and statuses
//if exit status != 0, should maybe not continue and update exit status
//find pattern
//kcnkscs | cat >> return 0 ..works
// cat | kjcnkdc >> return 127 (after ctrl+c, because cat working normally)
//          ..this does not work in minishell
int multiple_commands(t_biggie *bigs)
{
    int pid;
    int orig_stdout;
    int orig_stdin;
    int status;

    orig_stdout = dup(STDOUT_FILENO);
    orig_stdin = dup(STDIN_FILENO);
    if (orig_stdout == -1 || orig_stdin == -1)
    {
        perror("");
        return (1);
    }
    bigs->exit_status = check_before_multiple(bigs);
    if (bigs->exit_status != 0)
        return (bigs->exit_status);
    while (bigs->cmd->next != NULL && g_signal != SIGINT)
    {
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
            if (bigs->cmd->is_first == 1)
            {
                status = first_multiple(bigs);
                if (status != 0) // should i just return exit status wihtout check, would make more sense
                {
                    free_big(bigs);
                    exit (status);
                }
            }    
            else
                status = other_multiple(bigs);
            free_big(bigs);
            exit(status);
        }
        if (bigs->cmd->is_first == 1)
            close(bigs->pipe_cmd->pipe[1]);
        else
        {
            close(bigs->pipe_cmd->pipe[0]);
            close(bigs->pipe_cmd->next->pipe[1]);
            bigs->pipe_cmd = bigs->pipe_cmd->next;
        }
        if (bigs->cmd->redir_in != NULL)
            close_herepipe(bigs->cmd);
        bigs->cmd = bigs->cmd->next;
    }
    if (g_signal != SIGINT)
        bigs->exit_status = last_multiple(bigs);
    if (bigs->cmd->redir_in != NULL)
        close_herepipe(bigs->cmd);
    // while (wait(&status) > 1)
    //     ;
    return (bigs->exit_status);
}

int command_execution(t_biggie *bigs)
{
    t_command *head;

    g_signal = 0;
    bigs->cmd->is_first = 1;
    if (bigs->cmd->next == NULL)
    {
        bigs->exit_status = single_command(bigs);
        return (bigs->exit_status);
    }
    bigs->pipe_cmd = prepare_pipes(bigs->cmd);
    bigs->pipe_head = bigs->pipe_cmd;
    head = bigs->cmd;
    while (bigs->cmd->next != NULL)
    {
        bigs->cmd = bigs->cmd->next;
        bigs->cmd->envar = bigs->env;
        bigs->cmd->is_first = 0;
    }
    bigs->cmd = head;
    bigs->exit_status = multiple_commands(bigs);
    return(bigs->exit_status);
}
