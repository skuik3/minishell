/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:03:31 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/08/20 11:07:31 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int last_heredoc(t_redir *last)
{
    int pid;
    int pipe_hdc[2];
    char *promt;
    int status;

    if (pipe(pipe_hdc) == -1)
        return(ft_putstr_fd(ERR_PIPE, STDERR_FILENO), 1);
    pid = fork();
    if (pid < -1)
        return (ft_putstr_fd(ERR_FORK, STDERR_FILENO), 1);
    else if (pid == 0)
    {
        close(pipe_hdc[0]);
        promt = get_line_heredoc(last);
        write(pipe_hdc[1], promt, ft_strlen(promt));
        close(pipe_hdc[1]);
        exit(0);
    }
    close(pipe_hdc[1]);
    waitpid(pid, &status, 0);
    if (dup2(pipe_hdc[0], STDIN_FILENO) == -1)
        return (1);
    close(pipe_hdc[0]);
    return (0);
}

char *get_line_heredoc(t_redir *last)
{
    char *line;
    char *returned;

    returned = NULL;
    while (1)
    {
        write (STDOUT_FILENO, "> ", 3);
        line = get_next_line(STDIN_FILENO);
        if (ft_strcmp(line, ft_strjoin(last->filename, "\n")) == 0)
            break ;
        returned = ft_strjoin(returned, line);        
    }
    return (returned);
}

int redirecting_heredoc(t_redir *heredoc)
{
    char *promt;
    int pid;
    int status;

    pid = fork();
    if (pid < -1)
        return (ft_putstr_fd(ERR_FORK, STDERR_FILENO), 1);
    else if (pid == 0)
    {
        promt = get_line_heredoc(heredoc);
        exit(0);
    }
    waitpid(pid, &status, 0);
    return (status);
}

int do_heredoc(t_command *cmd)
{
    int i;
    int returned;
    int hdc;

    i = 0;
    returned = 0;
    hdc = where_last_heredoc(cmd, REDIR_HEREDOC);
    while (i < hdc)
    {
        if (cmd->redir_in[i]->type == REDIR_HEREDOC)
            returned = redirecting_heredoc(cmd->redir_in[i]);
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

int heredoc_present(t_redir **redir)
{
    int i;

    i = 0;
    while (redir[i] != NULL)
    {
        if (redir[i]->type == REDIR_HEREDOC)
            return (1);
        i++;
    }
    return (0);
}

int check_heredoc (t_command *cmd)
{
    int returned;

    while (cmd->next != NULL)
    {
        if (heredoc_present(cmd->redir_in) == 1)
            returned = do_heredoc(cmd);
        cmd = cmd->next;
    }
    if (cmd->next == NULL && cmd->is_first == 1) // for single command
    {
        if (heredoc_present(cmd->redir_in) == 1)
            returned = do_heredoc(cmd);
    }
    return (returned);
}
