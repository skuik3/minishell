/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nonbuiltins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:27:14 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/28 10:54:49 by anezkahavra      ###   ########.fr       */
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
// same as find_home, modify later
char *find_home(env_t *env)
{
    int i;
    char *variable;
    char *path;

    i = 0;
    while (env->mod[i] != NULL)
    {
        variable = find_variable(env->mod[i]);
        if (ft_strcmp(variable, "PATH") == 0)
        {
            path = malloc(sizeof(char) * (ft_strlen(env->mod[i] + 2)));
            if (path == NULL)
                return (ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), NULL);
            ft_strlcpy(path, &env->mod[i][5], ft_strlen(env->mod[i - 4]));
        }
        i++;
    }
    return (path);
}

char *command_path(t_command *cmd)
{
    char *env_path;
    char **arr_path;
    int i;

    i = 0;
    env_path = find_path(cmd->envar);
    arr_path = ft_split(env_path, ':');
    while (arr_path[i] != NULL)
    {
        if (access(cmd->command, F_OK) == 0)
            return (arr_path[i]);
        i++;
    }
    return (NULL);
}

// needed commands recognition
// very very basic functionality

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
        path = find_path(cmd);
        execve(path, cmd->arguments, cmd->envar);
    }
    else if (pid > 0)
        waitpid(pid, &status, 0); // if not use for check, status not needed >> NULL
    return (0);
}

