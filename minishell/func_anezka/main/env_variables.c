/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:29:02 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/31 22:55:57 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int copy_string(char **env, char *orig_env)
{
    int i;

    i = 0;
    while (orig_env[i] != '\0')
        i++;
    *env = malloc(sizeof(char) * (i + 1));
    if (*env == NULL)
        return (ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), 1);
    i = 0;
    while (orig_env[i] != '\0')
    {
        (*env)[i] = orig_env[i];
        i++;
    }
    (*env)[i] = '\0';
    return (0);
}

int saving_env(char ***env, char *envp[])
{
    int i;

    i = 0;
    while (envp[i] != NULL)
        i++;
    *env = malloc(sizeof(char *) * (i + 1));
    if (*env == NULL)
        return (ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), 1);
    i = 0;
    while (envp[i] != NULL)
    {
        copy_string(&(*env)[i], envp[i]);
        i++;
    }
    env[i] = NULL;
    return (0);
}