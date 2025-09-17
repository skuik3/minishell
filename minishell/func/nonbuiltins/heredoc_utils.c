/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:52:13 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/17 08:56:47 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


char *get_line_heredoc(t_redir *last)
{
    char *line;
    char *returned;

    returned = NULL;
    while (1 && g_signal != SIGINT)
    {
        write (STDOUT_FILENO, "> ", 3);
        line = get_next_line(STDIN_FILENO);
        if (ft_strcmp(line, ft_strjoin(ft_strdup(last->filename), "\n")) == 0)
            break ;
        returned = ft_strjoin(returned, line);        
    }
    return (returned);
}

int heredoc_present(t_redir **redir)
{
    int i;

    i = 0;
    if (redir == NULL)
        return (0);
    while (redir[i] != NULL)
    {
        if (redir[i]->type == REDIR_HEREDOC)
            return (1);
        i++;
    }
    return (0);
}

int last_heredoc_multiple(t_redir *last)
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
    waitpid(pid, &status, 0);
    close(last->pipe_forhdc[1]);
    if (g_signal == SIGINT) 
    {
        close(last->pipe_forhdc[0]);
        return (SIGINT);
    }
    return (0);
}

int do_heredoc_multiple(t_command *cmd)
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
    if (cmd->redir_in[i]->type == REDIR_HEREDOC)
       returned = last_heredoc_multiple(cmd->redir_in[i]);
    return (returned);
}
