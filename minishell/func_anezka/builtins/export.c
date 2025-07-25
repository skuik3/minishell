/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:08 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/22 10:48:34 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int counting_envlen(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
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
		return (ft_putstr_fd(ERR_MALLOC, 2), NULL);
	while (old_envp[i] != NULL)
	{
		new_envp[i] = old_envp[i];
		i++;
	}
	len = 0;
	new_envp[i] = malloc(sizeof(char) * (ft_strlen(new_arg) + 1));
	if (new_envp == NULL)
		return (ft_putstr_fd(ERR_MALLOC, 2), NULL);
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
	char *temp;

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
	int k;
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

//now added as a string, without recognizing variable and value, pr. JANA / should be JANA=''
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
    	envp->mod = put_envp(envp->mod, arguments[i]);
		i++;
	}
 // just fo easy check, delete later >> export with args is not printed
    get_order(envp->mod);
    run_env(envp->mod);
    return (0);
}

