/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:14:42 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/17 13:36:55 by anezka           ###   ########.fr       */
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
        free(present);
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

    variable = find_variable(argument);
    unset = malloc(sizeof(char *) * 2);
    if (unset == NULL)
    {
        perror("");
		return (NULL);
    }
    unset[0] = ft_strdup(variable);
    unset[1] = NULL;
    free(variable);
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

int check_variable(char *variable)
{
    int i;
    char *just_variable;

    i = 1;
    just_variable = find_variable(variable);
    if (ft_isalpha(just_variable[0]) != 1)
    {
        free(just_variable);
        return (1);
    }
    while (just_variable[i] != '\0')
    {
        if (ft_isalnum(just_variable[i]) != 1)
        {
            free(just_variable);
            return (1);
        }
        i++;
    }
    free(just_variable);
    return (0);
}
