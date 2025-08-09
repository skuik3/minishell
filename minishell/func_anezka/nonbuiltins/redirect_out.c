/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:03:31 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/08/09 12:16:39 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// 2> for redirecting error output / probably not needed 

int check_redirect(t_command *cmd)
{
    int returned;

    returned = 0;
    if (cmd->redir_in != NULL)
    {
        returned = redirect_in(cmd);
        if (returned == 1)
            return (1);

    }
    if (cmd->redir_out != NULL)
    {
        returned = redirect_out(cmd);
        if (returned == 1)
            return (1);
    }
    return (returned);
}

int redirecting_out(t_redir *redirout)
{
    int fd;

    if (access(redirout->filename, F_OK) == 0)
    {
        if (unlink(redirout->filename) == -1)
            return(ft_putstr_fd(ERR_FILE, STDERR_FILENO), 1);
    }
    fd = open(redirout->filename, O_RDWR | O_CREAT, SHELL_DEFAULT);
    if (fd == -1)
        return (ft_putstr_fd(ERR_FILE, 2), 1);
    close(fd);
    return (0);
}

int appending(t_redir *append)
{
    int fd;

    if (access(append->filename, F_OK) != 0)
        fd = open(append->filename, O_RDWR | O_CREAT, SHELL_DEFAULT);
    if (fd == -1)
        return (ft_putstr_fd(ERR_FILE, 2), 1);
    close (fd);
    return (0);
}

int last_redirect_out(t_redir *last)
{
    int fd;

    if (last->type == REDIR_OUT)
    {
        if (access(last->filename, F_OK) == 0)
        {
            if (unlink(last->filename) == -1)
                return(ft_putstr_fd(ERR_FILE, STDERR_FILENO), 1);  
        }
    }
    fd = open(last->filename, O_RDWR | O_CREAT | O_APPEND, SHELL_DEFAULT);
    if (fd == -1)
        return (ft_putstr_fd(ERR_FILE, 2), 1);
    if (dup2(fd, STDOUT_FILENO) == -1)
        return (ft_putstr_fd(ERR_DUP, STDERR_FILENO), 1);
    close(fd);
    return (0);
}

int redirect_out(t_command *cmd)
{
    int i;
    int returned;

    i = 0;
    returned = 0;
    while (cmd->redir_out[i + 1] != NULL)
    {
        if (cmd->redir_out[i]->type == REDIR_OUT)
            returned = redirecting_out(cmd->redir_out[i]);
        else if (cmd->redir_out[i]->type ==  REDIR_APPEND)
            returned = appending(cmd->redir_out[i]);
        i++;
    }
    returned = last_redirect_out(cmd->redir_out[i]);
    return (returned);
}
