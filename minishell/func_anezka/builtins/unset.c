/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:08 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/22 10:49:49 by anezkahavra      ###   ########.fr       */
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

int run_unset2(env_t *envp, char **arguments)
{
    int i;
    int unset;
    int   envp_len;
    char *variable;

    i = 0;
    unset = -1;
    if (arguments == NULL)
        return (ft_putstr_fd(ERR_ARG, 2), 1);
    variable = find_variable(arguments);
    envp_len = counting_envlen(envp->mod);
    while(envp->mod[i] != NULL)
    {
        if (envp->mod[i][0] == variable[0])
        {
            if (unset_variable(envp->mod[i], variable, i) != -2)
                unset = unset_variable(envp->mod[i], variable, i);
        }
        i++;
    }
    if (unset == -1)
        return (0);
    envp->mod = put_unset(envp->mod, unset);
    get_order(envp->mod);
    run_env(envp->mod);
    return (0);
}

int *find_unset(int *unset, char **arguments, env_t *envp)
{
    int i;
    char *variable;

    i = 0;
    while (arguments[i] != NULL)
    {
        variable = find_variable()
    }
}

int run_unset(env_t *envp, char **arguments)
{
    int i;
    int j;
    int arglen;
    int envplen;
    int *unset;

    i = 0;
    j = 0;
    if (arguments == NULL)
        return (ft_putstr_fd(ERR_ARG, 2), 1);
    arglen = counting_envlen(arguments);
    envplen = counting_envlen(envp->mod);
    unset = malloc(sizeof(int) * (arglen * envplen + 1));
    if (unset == NULL)
        return(ft_putstr_fd(ERR_MALLOC, 2), 1);
    unset = find_unset(unset, arguments, envp);
    
}
