/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:03:31 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/08/03 16:26:00 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int redirecting_in(t_redir *redirin)
{
    if (access(redirin->filename, F_OK) == -1)
        return(ft_putstr_fd(ERR_NOTFILE, STDOUT_FILENO), 1);
    return (0);   
}

// int redirecting_heredoc(t_redir *herdoc)
// {

// }

int last_redirect_in(t_redir *last)
{
    int fd;

    if (access(last->filename, F_OK) == -1)
        return(ft_putstr_fd(ERR_NOTFILE, STDOUT_FILENO), 1);
    fd = open(last->filename, O_RDWR | O_CREAT, SHELL_DEFAULT);
    if (dup2(fd, STDIN_FILENO) == -1)
        return(ft_putstr_fd(ERR_DUP, STDERR_FILENO), 1);
    close (fd);
    return (0);
}

int redirect_in(t_command *cmd)
{
    int i;

    i = 0;
    while (cmd->redir_in[i + 1] != NULL)
    {
        if (cmd->redir_in[i]->type == REDIR_IN)
            redirecting_in(cmd->redir_in[i]);
        // else if (cmd->redir_in[i]->type == REDIR_HEREDOC)
        //     redirecting_heredoc(cmd->redir_in[i]);
        i++;
    }
    last_redirect_in(cmd->redir_in[i]);
}
