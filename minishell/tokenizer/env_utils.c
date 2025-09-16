/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:15:00 by skuik             #+#    #+#             */
/*   Updated: 2025/09/16 15:12:18 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_env_vars(char *envp[])
{
    int count = 0;
    
    if (!envp)
        return (0);
    while (envp[count])
        count++;
    return (count);
}

int saving_env(char ***env, char *envp[])
{
    int count;
    int i;
    
    if (!env || !envp)
        return (-1);
        
    count = count_env_vars(envp);
    *env = malloc(sizeof(char *) * (count + 1));
    if (!*env)
        return (-1);
        
    i = 0;
    while (i < count)
    {
        (*env)[i] = ft_strdup(envp[i]);
        if (!(*env)[i])
        {
            // Free previously allocated strings on failure
            while (i > 0)
            {
                i--;
                free((*env)[i]);
            }
            free(*env);
            *env = NULL;
            return (-1);
        }
        i++;
    }
    (*env)[count] = NULL;
    return (0);
}