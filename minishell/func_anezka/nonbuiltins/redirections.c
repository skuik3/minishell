/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:03:31 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/23 12:31:24 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// if no number infront, automatically 1 (could use 2> for redirecting error output)

int redirecting_in(t_command *cmd)
{
    int fd;
    int buff_len;
    int dest;

    dest = 0;
    while (cmd->redir_in[dest] != NULL)
        dest++;
    buff_len = ft_strlen(cmd->arguments[0]);
    if (access(cmd->redir_in[dest - 1], F_OK) == 0)
    {
        if (unlink(cmd->redir_in[dest - 1]) == -1){
            ft_putstr_fd(ERR_FILE, 2);
            return (1);
        }
    }
    fd = open(cmd->redir_in[dest - 1], O_RDWR | O_CREAT, SHELL_DEFAULT);
    if (fd == -1)
    {
        ft_putstr_fd(ERR_FILE, 2);
        return (1);
    }
    write(fd, cmd->arguments[0], buff_len); 
    close(fd);
    return (0);
}

// int redirecting_error(char *str)
// {

// }

int appending(t_command *cmd)
{
    int fd;
    int buff_len;
    int dest;

    buff_len = ft_strlen(cmd->arguments[0]);
    dest = 0;
    while (cmd->append[dest] != NULL)
        dest++;
    if (access(cmd->append[dest - 1], F_OK) != 0)
        fd = open(cmd->append[dest - 1], O_RDWR | O_CREAT, SHELL_DEFAULT);
    fd = open(cmd->append[dest - 1], O_RDWR | O_APPEND, SHELL_DEFAULT);
    if (fd == -1)
    {
        ft_putstr_fd(ERR_FILE, 2);
        return (1);
    }
    // printf("%d", fd);
    write(fd, "\n", 1);
    write (fd, cmd->arguments[0], buff_len);
    write(fd, "\n", 1);
    close(fd);
    return (0);
}
// pulls input from a file
// int redirecting_out(char *str)
// {
//     int fd;
//     int buff_len;

//     return (0);
// }

