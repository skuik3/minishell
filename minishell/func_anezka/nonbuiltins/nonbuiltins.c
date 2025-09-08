/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nonbuiltins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:27:14 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/08 16:09:33 by anezkahavra      ###   ########.fr       */
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
    if (i == len)
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
        path = ft_strjoin(arr_path[i], "/");
        path = ft_strjoin(path, cmd->command);
        if (access(path, F_OK) == 0)
            return (path);
        i++;
    }
    return (NULL);
}

char **adding_command(t_command *cmd)
{
    char **cmdw_args;
    int arr_len;
    int i;

    arr_len = counting_envlen(cmd->arguments);
    cmdw_args = malloc(sizeof(char *) * (arr_len + 2));
    if (cmdw_args == NULL)
    {
        perror("");
        return (NULL);
    }
    cmdw_args[0] = ft_strdup(cmd->command);
    i = 1;
    while (cmd->arguments[i - 1] != NULL)
    {
        cmdw_args[i] = ft_strdup(cmd->arguments[i - 1]);
        i++;
    }
    cmdw_args[i] = NULL;
    return(cmdw_args);
}

int executing(t_command *cmd)
{
    char *path;
    char **cmdw_args;

    cmdw_args = adding_command(cmd);
    if (cmdw_args == NULL)
    {
        perror("");
        return (1);
    }
    if (is_path(cmd->command) == 0)
    {
        if (execve(cmd->command, cmdw_args, cmd->envar->mod) == -1)
        {
            perror("");
            return (1);
        }
    }
    else if (is_path(cmd->command) != 0)
    {
        path = command_path(cmd);
        if (path == NULL)
        {
            write(1, "Command not found\n", 19);
            return (127);
        }
        if (execve(path, cmdw_args, cmd->envar->mod) == -1)
        {
            perror("");
            return (1);
        }
    }
    return (0);
}

