/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:08 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/15 10:25:00 by skuik            ###   ########.fr       */
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
		new_arg = ft_strjoin(argument, "''");
	else //if (argument[i] == '\0')
		new_arg = ft_strjoin(argument, "=''");
	return (new_arg);
}

char  **put_envp(char **old_envp, char *new_arg)
{
	char **new_envp;
	int len;
	int i;

	i = 0;
	len = counting_envlen(old_envp);
	new_envp = malloc(sizeof(char *) * (len + 2));
	if (new_envp == NULL)
	{
		perror("");
		return (NULL);
	}
	while (old_envp[i] != NULL)
	{
		new_envp[i] = old_envp[i];
		i++;
	}
	len = 0;
	new_envp[i] = malloc(sizeof(char) * (ft_strlen(new_arg) + 1));
	if (new_envp == NULL)
	{
		perror("");
		return (NULL);
	}
	while (new_arg[len] != '\0')
	{
		new_envp[i][len] = new_arg[len];
		len++;
	}
	new_envp[i][len] = '\0';
	new_envp[i + 1] = NULL;
	free (old_envp);
	return (new_envp);
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

int get_order(char **envp)
{
	int i;
	char *temp;
	int swapped;

	i = 0;
	while (envp[i] != NULL && envp[i + 1] != NULL)
	{
		swapped = 0;
		if (envp[i][0] == envp[i + 1][0])
			swapped = inner_check(envp, i);
		if (swapped == 1 || envp[i][0] > envp[i + 1][0])
		{
			temp = envp[i];
			envp[i] = envp[i + 1];
			envp[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	return (0);
}

int run_export(env_t *envp, char **arguments)
{
    int   i;
	char *add_variable;
	char **unset;

    i = 0;
    if (arguments == NULL)
    {
        get_order(envp->mod);
        run_env(envp->mod);
        return (0);
    }
	while (arguments[i] != NULL)
	{
		add_variable = adding_variable(arguments[i]);
		if (check_variable(add_variable) == 1)
		{
			write(1, "not a valid identifier\n", 24);
			return (1);
		}
		if (variable_present(find_variable(add_variable), envp) == 0)
		{
			if (value_present(arguments[i]) == 0)
			{
				unset = prepare_unset(arguments[i]);
				run_unset(envp, unset);
			}
			else
				return (0);
		}
		envp->mod = put_envp(envp->mod, add_variable);
		i++;
	}
 // just fo easy check, delete later
    get_order(envp->mod);
    run_env(envp->mod);
    return (0);
}

