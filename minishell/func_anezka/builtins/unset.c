/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:08 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/16 21:46:34 by anezkahavra      ###   ########.fr       */
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
        return (ft_putstr_fd(ERR_MALLOC, 2), NULL);
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
		return (ft_putstr_fd(ERR_MALLOC, 2), NULL);
    while (i < unset)
    {
       new_envp[i] = old_env[i];
       i++; 
    }
    i = unset + 1;
    while (old_env[i] != NULL)
    {
        new_envp[i] = old_env[i];
        i++; 
    }
    new_envp[i] = NULL;
    free(old_env);
    return (new_envp);
}

int run_unset(env_t *envp, char *arguments)
{
    int i;
    int j;
    int unset;
    int   envp_len;
    char *variable;

    i = 0;
    j = 0;
    if (arguments == NULL)
        return (ft_putstr_fd(ERR_MALLOC, 2), 1);
    variable = find_variable(arguments);
    envp_len = counting_envlen(envp->mod);
    while(envp->mod[i] != NULL)
    {
        if (envp->mod[i][j] == variable[j])
        {
            if (unset_variable(envp->mod[i], variable, i) != -2)
                unset = unset_variable(envp->mod[i], variable, i);
        }
        i++;
    }
    envp->mod = put_unset(envp->mod, unset);
    // get_order(new_envp->mod);
    // run_env(new_envp->mod);
    return (0);
}