/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nonbuiltins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:27:14 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/28 13:49:06 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_path(char *command)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(command);
    while (command[i] != '\0')
    {
        if (command[i] == '/')
            break ;
        i++;
    }
    if (i == (len + 1))
        return (1);
    return (0);
}

char *command_path(t_command *cmd)
{
    char *env_path;
    char **arr_path;
    int i;
    char *path;

    i = 0;
    env_path = find_path(cmd->envar, "PATH");
    arr_path = ft_split(env_path, ':');
    while (arr_path[i] != NULL)
    {
        path = ft_strjoin(arr_path[i], cmd->command);
        if (access(path, F_OK) == 0)
            return (path);
        i++;
    }
    return (NULL);
}


// maybe check with acces if file exist >> possible error
// maybe check status if child process works correctly
int executing(t_command *cmd)
{       
    //now defined, later when tokenization works, should be generally usable
    // char *const argv[] = {"ls", "-l", NULL}; depends on tokenization from readline, do later
    int pid;
    int status;
    char *path;

    pid = fork();
    if (pid < -1)
    {
        ft_putstr_fd(ERR_FORK, STDERR_FILENO);
        return (1);
    }
    if (is_path(cmd->command) == 0 && pid == 0)
        execve(cmd->command, cmd->arguments, cmd->envar);
    else if (is_path(cmd->command) != 0 && pid == 0)
    {
        path = command_path(cmd);
        execve(path, cmd->arguments, cmd->envar);
    }
    else if (pid > 0)
        waitpid(pid, &status, 0); // if not use for check, status not needed >> NULL
    return (0);
}

