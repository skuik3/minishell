/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:08 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/12 10:07:56 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *find_variable(char *arguments)
{
    char *variable;
    int i;
    int len;

    len = 0;
    while (arguments[len] != '\0' && arguments[len] != '=')
        len++;
    variable = malloc(sizeof(char) * (len + 1));
    if (variable == NULL)
    {
        perror("");
        return (NULL);
    }
    i = 0;
    while (arguments[i] != '\0' && arguments[i] != '=')
    {
        variable[i] = arguments[i];
        i++;
    }
    variable[i] = '\0';
    return(variable);
}

char **put_unset(char **old_env, int unset)
{
    int i;
    int len;
    char **new_envp;

    i = 0;
    len = counting_envlen(old_env);
    new_envp = malloc(sizeof(char *) * (len));
    if (new_envp == NULL)
    {
        perror("");
        return (NULL);
    }
    while (i < unset)
    {
       new_envp[i] = old_env[i];
       i++; 
    }
    while (old_env[i + 1] != NULL)
    {
        new_envp[i] = old_env[i + 1];
        i++; 
    }
    new_envp[i] = NULL;
    // run_env(new_envp);
    free(old_env);
    return (new_envp);
}

int unset_position(char *envp, char *variable, int i)
{
    int j;
    int len;

    j = 0;
    len = ft_strlen(variable);
    while (envp[j] != '\0' && variable[j] != '\0')
    {
        if (envp[j] != variable[j])
            break ;
        j++;
    }
    if (envp[j] == '=' && j == len && variable[j] == '\0')
        return (i);
    return (-2);
}

int find_unset(char *arguments, env_t *envp)
{
    char *variable;
    int i;
    int unset;

    i = 0;
    variable = find_variable(arguments);
    if (ft_strcmp(variable, arguments) != 0) //proc
        return (free(variable), 1);
    while (envp->mod[i] != NULL)
    {
        if (envp->mod[i][0] == variable[0])
        {
            unset = unset_position(envp->mod[i], variable, i);
            if (unset != -2)
                break;
        }
        i++;
    }
    return (unset);
}

int unseting(env_t *envp, char *arguments)
{
    int i;
    int unset;

    i = 0;
    unset = find_unset(arguments, envp);
    if (unset != -2)
    {
        envp->mod = put_unset(envp->mod, unset);
        if (envp->mod == NULL)
            return (1);
    }
    return (0);
}

int run_unset(env_t *envp, char **arguments)
{
    int i;
    int returned;

    i = 0;
    returned = 0;
    if (arguments == NULL)
        return (0);
    while (arguments[i])
    {
        returned = unseting(envp, arguments[i]);
        i++;
    }
    //for check
    get_order(envp->mod);
    run_env(envp->mod);
    return (returned);
}