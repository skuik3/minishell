/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:43:42 by ehasalu           #+#    #+#             */
/*   Updated: 2025/08/10 16:43:28 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_ft_calloc(size_t nmemb, size_t size)
{
	unsigned int	i;
	void			*temp;
	size_t			test;
	int				c;

	c = 0;
	if (nmemb == 0 || size == 0)
	{
		temp = malloc(0);
		return (temp);
	}
	test = nmemb * size;
	if (test / nmemb != size)
		return (NULL);
	temp = malloc(size * nmemb);
	if (!temp)
		return (NULL);
	i = 0;
	while (i < (size * nmemb))
	{
		((unsigned char *)temp)[i] = (unsigned char)c;
		i++;
	}
	return (temp);
}

char	*gnl_ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

size_t	gnl_ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	char	*res;

	i = 0;
	res = (char *)gnl_ft_calloc(sizeof(char), (gnl_ft_strlen(s1) + gnl_ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		res[i] = *s2;
		i++;
		s2++;
	}
	res[i] = '\0';
	//free (s1);
	return (res);
}

char	*gnl_ft_strdup(char *s)
{
	size_t	i;
	size_t	len;
	char	*dest;

	len = gnl_ft_strlen(s);
	i = 0;
	dest = (char *)gnl_ft_calloc(sizeof(char), (len + 1));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
