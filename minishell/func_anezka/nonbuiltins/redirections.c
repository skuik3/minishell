/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:03:31 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/23 16:06:09 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// if no number infront, automatically 1 (could use 2> for redirecting error output)

int redirecting_in(t_command *cmd)
{
    int fd;
    int i;
    int j;

    i = 0;
    while (cmd->redir_in[i] != NULL)
    {
        if (access(cmd->redir_in[i], F_OK) == 0)
        {
            if (unlink(cmd->redir_in[i]) == -1)
                return (ft_putstr_fd(ERR_FILE, 2), 1);
        }
        fd = open(cmd->redir_in[i], O_RDWR | O_CREAT, SHELL_DEFAULT);
        if (fd == -1)
            return (ft_putstr_fd(ERR_FILE, 2), 1);
        j = 0;
        while (cmd->arguments[j] != NULL)
        {
            ft_putstr_fd(cmd->arguments[j], fd);
            ft_putstr_fd(" ", fd);
            j++;
        }
        ft_putstr_fd("\n", fd);
        close (fd);
        i++;
    }
    return (0);
}


// int redirecting_error(char *str)
// {

// }

int appending(t_command *cmd)
{
    int fd;
    int i;
    int j;
    
    i = 0;
    while (cmd->append[i] != NULL)
    {
        if (access(cmd->append[i], F_OK) != 0)
            fd = open(cmd->append[i], O_RDWR | O_CREAT, SHELL_DEFAULT);
        fd = open(cmd->append[i], O_RDWR | O_APPEND, SHELL_DEFAULT);
        if (fd == -1)
            return (ft_putstr_fd(ERR_FILE, 2), 1);
        j = 0;
        while (cmd->arguments[j] != NULL)
        {
            ft_putstr_fd(cmd->arguments[j], fd);
            ft_putstr_fd(" ", fd);
            j++;
        }
        ft_putstr_fd("\n", fd);
        close (fd);
        i++;
    }
    return (0);
}

// pulls input from a file
int redirecting_out(t_command *cmd)
{
    int fd;
    int buff_len;

    if (access(cmd->heredoc)
    return (0);
}

