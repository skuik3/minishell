/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:14:42 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/28 16:29:29 by anezkahavra      ###   ########.fr       */
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

char **exchange_values(char **envp, char *exchange)
{
    int i;
    int spot;
    char *variable;

    i = 0;
    variable = find_variable(exchange);
    while (envp[i] != NULL)
    {
        if (unset_variable(envp[i], exchange, i) != -2)
            envp[i] = exchange;
        i++;
    }
    return (envp);
}


