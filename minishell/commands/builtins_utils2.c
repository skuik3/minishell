/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:21:28 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/14 15:41:04 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

int counting_envlen(char *envp[])
{
	int i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

int put_envp(char *envp, char *new_envp[], int i)
{
	int k;

	new_envp[i] = malloc(sizeof(char) * ft_strlen(envp) + 1);
	if (new_envp[i] == NULL)
	{
		write (STDERR_FILENO, "Error mallocing\n", 17);
		return (1);
	}
	k = 0;
	while (envp[k] != '\0')
	{
		new_envp[i][k] = envp[k];
		k++;
	}
	new_envp[i][k] = '\0';
	return (0);
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
		j++;
	}
	if (envp[i][j] != '\0' && envp[i + 1][j] == '\0')
		return (1);
	return (0);
}

int get_order(char *envp[])
{
	int i;
	int k;
	char *temp;
	int swapped;

	i = 0;
	k = 0;
	while (envp[i + 1] != NULL)
	{
		// swapped = 0;
		// if (envp[i][k] == envp[i + 1][k])
		// 	swapped = inner_check(envp, i);
		if (/* swapped == 1 ||  */envp[i][k] > envp[i + 1][k])
		{
			temp = envp[i];
			envp[i] = envp[i + 1];
			envp[i + 1] = temp;
			i = 0;
		}
		i++;
	}
	return (0);
}

