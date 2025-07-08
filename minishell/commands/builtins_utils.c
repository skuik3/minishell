/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:38:20 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/08 09:58:24 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;

	while ((s1[i] != '\0') && (s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_numstrings(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (i != 0 && s[i] == c && s[i - 1] != c)
			j++;
		i++;
	}
	if (s[ft_strlen(s) - 1] == c)
		j = j - 1;
	if (s[0] == '\0')
		j = j - 1;
	return (j + 1);
}

unsigned int	findend(const char *s, int c, int i)
{
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i - 1] != c)
			break ;
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int					str_i;
	unsigned int		i;
	char				**result;

	result = malloc(((ft_numstrings(s, c)) + 1) * (sizeof(char *)));
	if (result == NULL)
		return (NULL);
	i = 0;
	str_i = 0;
	while (i < (ft_strlen)(s))
	{
		while (s[i] == c)
			i++;
		if (i < findend(s, c, i))
		{
			result[str_i] = malloc(sizeof(char) * ((findend(s, c, i) - i) + 1));
			if (result[str_i] == NULL)
				return (NULL);
			ft_strlcpy(result[str_i], &(s[i]), (findend(s, c, i) - i + 1));
			str_i++;
			i = findend(s, c, i);
		}
	}
	result[str_i] = NULL;
	return (result);
}