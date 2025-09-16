/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:03:31 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/16 15:28:59 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int last_heredoc(t_redir *last)
{
    int pid;

    char *promt;
    int status;

    last->pipe_forhdc = malloc(sizeof(int) * 2);
    if (last->pipe_forhdc == NULL)
        return (1);
    if (pipe(last->pipe_forhdc) == -1)
        return (1);
    signal(SIGINT, handle_signal_child);
    pid = fork();
    if (pid < -1)
        return (1);
    else if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        close(last->pipe_forhdc[0]);
        promt = get_line_heredoc(last);
        write(last->pipe_forhdc[1], promt, ft_strlen(promt));
        close(last->pipe_forhdc[1]);
        exit(0);
    }
    close(last->pipe_forhdc[1]);
    waitpid(pid, &status, 0);
    if (g_signal == SIGINT)
    {
        close(last->pipe_forhdc[0]);
        return (SIGINT);
    }
    return (0);
}

//check if casting does not affect
int redirecting_heredoc(t_redir *heredoc)
{
    char *promt;
    int pid;
    int status;

    signal(SIGINT, handle_signal_child);
    pid = fork();
    if (pid < -1)
        return (1);
    else if (pid == 0)
    {        
        signal(SIGINT, SIG_DFL);
        promt = get_line_heredoc(heredoc);
        (void)promt;
        exit(0);
    }
    if (g_signal == SIGINT)
        return (SIGINT);
    waitpid(pid, &status, 0);
    return (status);
}

int do_heredoc(t_command *cmd)
{
    int i;
    int returned;

    i = 0;
    returned = 0;
    while (cmd->redir_in[i + 1] != NULL)
    {
        if (cmd->redir_in[i]->type == REDIR_HEREDOC)
            returned = redirecting_heredoc(cmd->redir_in[i]);
        if (returned == SIGINT)
            return(returned);
        i++;
    }
    while (cmd->redir_in[i] != NULL)
    {
        if (cmd->redir_in[i]->type == REDIR_HEREDOC)
            returned = last_heredoc(cmd->redir_in[i]);
        i++;
    }
    return (returned);
}

int check_heredoc(t_command *cmd)
{
    int returned;

    returned = 0;
    if (cmd->next == NULL && cmd->is_first == 1)
    {
        if (heredoc_present(cmd->redir_in) == 1)
            returned = do_heredoc(cmd);
        return (returned);
    }
    while (cmd != NULL)
    {
        if (heredoc_present(cmd->redir_in) == 1)
            returned = do_heredoc_multiple(cmd);
        if (returned == SIGINT)
            return(returned);
        cmd = cmd->next;
    }
    return (returned);
}
