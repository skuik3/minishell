/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:08 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/11 13:27:53 by anezkahavra      ###   ########.fr       */
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

int unset_variable(char *envp, char *variable, int i)
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

char **put_unset(char **old_env, int unset)
{
    int i;
    int len;
    char **new_envp;

    i = 0;
    len = counting_envlen(old_env);
    new_envp = malloc(sizeof(char *) * (len + 1));
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

int *find_unset(int *unset, char **arguments, env_t *envp)
{
    int i;
    int j;
    char *variable;

    j = 0;
    while (arguments[j] != NULL)
    {
        variable = find_variable(arguments[j]);
        if (ft_strcmp(variable, arguments[j]) != 0)
            return (free(variable), NULL);
        i = 0;
        unset[j] = -1;
        while (envp->mod[i] != NULL)
        {
            if (envp->mod[i][0] == variable[0])
            {
                if (unset_variable(envp->mod[i], arguments[j], i) != -2)
                {
                    unset[j] = unset_variable(envp->mod[i], variable, i);
                    return (unset);
                }
        
            }
            i++;
        }
        j++;
    }
    free(variable);
    unset[j] = '\0';
    return (unset);
}

int run_unset_cont(env_t *envp, char **arguments)
{
    int i;
    int j;
    int arglen;
    int envplen;
    int *unset;

    i = 0;
    j = 0;
    if (arguments[0] == NULL)
        return (ft_putstr_fd(ERR_ARG, STDERR_FILENO), 1);
    // arglen = counting_envlen(arguments);
    envplen = counting_envlen(envp->mod);
    unset = malloc(sizeof(int) * (arglen * envplen + 1));
    if (unset == NULL)
    {
        perror("");
        return (1);
    }
    unset = find_unset(unset, arguments, envp);
    if (unset == NULL) //check, dont delete
        return (0);
    while (unset[i] != '\0')
    {
        if (unset[i] != -1)
            envp->mod = put_unset(envp->mod, unset[i]);
        i++;
    }
    //for check
    get_order(envp->mod);
    run_env(envp->mod);
    return (0);
}

int run_unset(env_t *envp, char **arguments)
{
    int i;
    int returned;

    i = 0;
    returned = 0;
    while (*arguments)
    {
        returned = run_unset_cont(envp, arguments);
        arguments++;
    }
    return (returned);
}