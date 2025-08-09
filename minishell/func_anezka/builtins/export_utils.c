/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:14:42 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/08/06 14:18:18 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int variable_present(char *variable, env_t *envp)
{
    int i;
    char *present;

    i = 0;
    while (envp->mod[i] != NULL)
    {
        present = find_variable(envp->mod[i]);
        if (ft_strcmp(variable, present) == 0)
            return (0);
        i++;
    }
    return (1);
}

int counting_envlen(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

char **prepare_unset(char *argument)
{
    char **unset;
    char *variable;
    int len;

    variable = find_variable(argument);
    len = ft_strlen(variable);
    unset = malloc(sizeof(char *) * 2);
    if (unset == NULL)
		return (ft_putstr_fd(ERR_MALLOC, 2), NULL);
    unset[0] = ft_strdup(variable);
    unset[1] = NULL;
    return (unset);
}

int value_present(char *argument)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(argument);
    while (argument[i] != '\0')
    {
        if (argument[i] == '=')
            break;
        i++;
    }
    if (i == len || (i == (len + 1) && argument[len] == '='))
        return (1);
    return (0);
}

