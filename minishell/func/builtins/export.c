/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:08 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/17 13:38:08 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *adding_variable(char *argument)
{
	int i;
	int len;
	char *new_arg;

	i = 0;
	len = ft_strlen(argument);
	while ((argument[i] != '\0'))
	{
		if (argument[i] == '=')
			break;
		i++;
	}
	if (i != len && argument[i + 1] != '\0')
		return (argument);
	if (argument[i] != '\0')
		new_arg = ft_strjoin(ft_strdup(argument), "''");
	else
		new_arg = ft_strjoin(ft_strdup(argument), "=''");
	return (new_arg);
}

int inner_check(char *envp[], int i)
{
	int j;

	j = 0;
	while (envp[i][j] != '\0' && envp[i + 1][j] != '\0')
	{
		if (envp[i][j] > envp[i + 1][j])
			return (1);
		else if (envp[i][j] < envp[i + 1][j])
			return (0);
		j++;
	}
	if (envp[i][j] != '\0' && envp[i + 1][j] == '\0')
		return (1);
	return (0);
}

int export_argument(env_t *envp, char *argument)
{
	char *add_variable;
	char **unset;
	char *var;

	add_variable = adding_variable(argument);
	var = find_variable(add_variable);
	if (check_variable(add_variable) == 1)
	{
		write(1, "not a valid identifier\n", 24);
		free(var);
		if (value_present(argument) != 0)
			free(add_variable);
		return (1);
	}
	if (variable_present(var, envp) == 0)
	{
		if (value_present(argument) == 0)
		{
			unset = prepare_unset(argument);
			run_unset(envp, unset);
		}
	}
	envp->mod = put_envp(envp->mod, add_variable);
	free(var);
	if (value_present(argument) != 0)
		free(add_variable);
	return (0);
}

int run_export(env_t *envp, char **arguments)
{
    int   i;

    i = 0;
    if (arguments == NULL)
    {
        get_order(envp->mod);
        run_env(envp->mod);
        return (0);
    }
	while (arguments[i] != NULL)
	{
		export_argument(envp, arguments[i]);
		i++;
	}
 // just fo easy check, delete later
    get_order(envp->mod);
    run_env(envp->mod);
    return (0);
}
