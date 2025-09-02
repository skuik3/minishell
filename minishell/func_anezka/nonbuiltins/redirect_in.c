/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:03:31 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/02 14:09:48 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int where_last_heredoc(t_command *cmd, int rdhc)
{
    int i;
    int heredoc;
    int redir;

    i = 0;
    redir = -1;
    heredoc = -1;
    while(cmd->redir_in[i] != NULL)
    {
        if (cmd->redir_in[i]->type == REDIR_IN)
            redir = i;
        else if (cmd->redir_in[i]->type == REDIR_HEREDOC)
            heredoc = i;
        i++;
    }
    if (rdhc == REDIR_IN)
        return (redir);
    else if (rdhc == REDIR_HEREDOC)
        return (heredoc);
    return (-1);
}

int redirecting_in(t_redir *redirin)
{
    if (access(redirin->filename, F_OK) == -1)
        return(ft_putstr_fd(ERR_NOTFILE, STDOUT_FILENO), 1);
    return (0);   
}

int last_redirect_in(t_redir *last)
{
    int fd;
    char *input;
    int returned;

    returned = 0;
    if (access(last->filename, F_OK) == -1) {
        return(ft_putstr_fd(ERR_NOTFILE, STDOUT_FILENO), 1);
    }
    fd = open(last->filename, O_RDWR | O_CREAT, SHELL_DEFAULT);
    if (dup2(fd, STDIN_FILENO) == -1)
        return(ft_putstr_fd(ERR_DUP, STDERR_FILENO), 1);
    close (fd);
    return (returned);
}

int redirect_in(t_command *cmd)
{
    int i;
    int redir;
    int returned;

    i = 0;
    returned = 0;
    // redir = where_last_heredoc(cmd, REDIR_IN);
    while (cmd->redir_in[i + 1] != NULL)
    {
        if (cmd->redir_in[i]->type == REDIR_IN)
            returned = redirecting_in(cmd->redir_in[i]);
        i++;
    }
    while (cmd->redir_in[i] != NULL)
    {
        if (cmd->redir_in[i]->type == REDIR_IN)
            returned = last_redirect_in(cmd->redir_in[i]);
        else {
            if (cmd->redir_in[i]->pipe_forhdc != NULL)
                dup2(cmd->redir_in[i]->pipe_forhdc[0], STDIN_FILENO);
            returned = 0;
        }
        i++;
    }
    return (returned);
}
