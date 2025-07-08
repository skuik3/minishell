/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:53:24 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/08 15:25:41 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int run_cd(char *path) //issues with absolute path? todo
{
    if (chdir(path) != 0)
    {
        write(STDERR_FILENO, "Error\n", 6);
        return (1);
    }
    run_pwd();
    return (0);
}

int run_echo(char **string)
{
    int i;
    int k;

    i = 2;
    if (string[2] == NULL)
    {
        write(STDOUT_FILENO, "\n", 1);
        return (0);
    }
    if (ft_strcmp(string[2], "-n") == 0)
        i++;
    while (string[i] != NULL)
    {
        k = 0;
        while (string[i][k] != '\0')
        {
            write(STDOUT_FILENO, &string[i][k], 1);
            k++;
        }
        if (string[i + 1] != NULL)
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (ft_strcmp(string[2], "-n") != 0) //adding flag
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}

int run_pwd(void)
{
    char *wd;
    char buff[PATH_MAX + 1];
    int i;

    wd = getcwd(buff, PATH_MAX + 1);
    if (wd != NULL)
    {
        i = 0;
        while (wd[i] != '\0')
        {
            write(STDOUT_FILENO, &wd[i], 1);
            i++;
        }
        write(STDOUT_FILENO, "\n", 1);
    }
    return (0);
}

int run_env(char *envp[])
{
    int i;

    i = 0;
    while (envp[i] != NULL)
    {
        printf("%s\n", envp[i]);
        i++;
    }
    return (0);
}

int run_exit(void)
{
    exit(0);
}

int run_export(char *envp[], char *arguments)
{
    int i;
    char *name;
    char *value;

    if (arguments == NULL)
    {
        i = 0;
        while (envp[i] != NULL)
        {
        printf("%s\n", envp[i]);
        i++;
        }  
    }
    // cant use setenv, probably will have to modify existing file consisting with environment variables 
    // saved from main
    // when printing or working with env >> using new version (probably struct pointer with old/new verisons)
    else
        setenv(name, value, 0); //if not 0 and name already exists, overwrites name
    return (0);
    //check if added correctly, in shell by abc
}