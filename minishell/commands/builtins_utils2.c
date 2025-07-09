/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:21:28 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/09 11:10:40 by anezkahavra      ###   ########.fr       */
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

int find_start(char *envp[], char *arguments)
{
	int i;
	int k;
	char *variable;

	i = 0;
	while (envp[i] != NULL)
	{
		k = 0;
		while (envp[i][k] < arguments[k])
			i++;
		if (envp[i][k] == arguments[k])
		{
			while[envp[i][k] != arguments[k]]
		}
	}
	return (i);
}
