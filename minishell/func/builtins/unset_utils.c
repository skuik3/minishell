/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:58:46 by anezka            #+#    #+#             */
/*   Updated: 2025/09/16 15:19:05 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
    new_envp[i] = ft_strdup(new_arg);
	new_envp[i + 1] = NULL;
	free (old_envp);
	return (new_envp);
}

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
