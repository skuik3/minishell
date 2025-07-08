/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:03:31 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/08 11:07:46 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// if no number infront, automatically 1 (could use 2> for redirecting error output)

int redirecting(char *str)
{
    int fd;
    int buff_len;

    buff_len = ft_strlen(str);
    if (access("name_of_file", F_OK) == 0)
    {
        if (unlink("name_of_file") == -1){
            write(STDERR_FILENO, "Error opening/creating a file\n", 31);
            return (1);
        }
    }
    fd = open("name_of_file", O_RDWR | O_CREAT, SHELL_DEFAULT);
    if (fd == -1)
    {
        write(STDERR_FILENO, "Error opening/creating a file\n", 31);
        return (1);
    }
    write(fd, str, buff_len); 
    close(fd);
    return (0);
}

int appending(char *str)
{
    int fd;
    int buff_len;

    buff_len = ft_strlen(str);
    if (access("name_of_file", F_OK) != 0)
        fd = open("name_of_file", O_RDWR | O_CREAT, SHELL_DEFAULT);
    fd = open("name_of_file", O_RDWR | O_APPEND, SHELL_DEFAULT);
    if (fd == -1)
    {
        write(STDERR_FILENO, "Error opening/creating a file\n", 31);
        return (1);
    }
    printf("%d", fd);
    write(fd, "\n", 1);
    write (fd, str, buff_len);
    write(fd, "\n", 1);
    close(fd);
    return (0);
}

