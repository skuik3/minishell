/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:38:52 by skuik             #+#    #+#             */
/*   Updated: 2025/03/07 16:15:32 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

size_t	ft_wordcount(char const *s, char c)
{
	size_t	word;

	if (!s)
		return (0);
	word = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			word++;
			while (*s != c && *s)
				s++;
		}
	}
	return (word + 1);
}

size_t	ft_wordlen(char const *s, char c, int i)
{
	size_t	len;

	len = 0;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		word;
	int		len;
	char	**str;

	i = 0;
	j = -1;
	word = ft_wordcount(s, c);
	str = ft_calloc(word, sizeof(char *));
	if (str == NULL)
		return (NULL);
	while (++j < word - 1)
	{
		while (s[i] == c)
			i++;
		len = ft_wordlen(s, c, i);
		str[j] = ft_substr(s, i, len);
		i += len;
	}
	str[j] = NULL;
	return (str);
}

// static int	ar_mal(char **result, int location, size_t buffer)
// {
// 	result[location] = malloc(buffer);
// 	if (result[location] == NULL)
// 		return (1);
// 	return (0);
// }

// static int	wordscpy(char **result, char const *s, char c)
// {
// 	size_t	len;
// 	int		i;

// 	i = 0;
// 	while (*s)
// 	{
// 		len = 0;
// 		while (*s && *s == c)
// 			++s;
// 		while (*s && *s != c)
// 		{
// 			++len;
// 			++s;
// 		}
// 		if (len)
// 		{
// 			if (ar_mal(result, i, len + 1))
// 				return (1);
// 			ft_strlcpy(result[i], s - len, len + 1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// static size_t	count_words(char const *s, char c)
// {
// 	size_t	words;
// 	bool	state;

// 	words = 0;
// 	while (*s)
// 	{
// 		state = false;
// 		while (*s && *s == c)
// 			s++;
// 		while (*s && *s != c)
// 		{
// 			if (!state)
// 			{
// 				words++;
// 				state = true;
// 			}
// 			s++;
// 		}
// 	}
// 	return (words);
// }

// char	**ft_split(char const *s, char c)
// {
// 	size_t	words;
// 	char	**result;

// 	words = 0;
// 	words = count_words(s, c);
// 	result = ft_calloc(words + 1, sizeof(char *));
// 	if (result == NULL)
// 		return (NULL);
// 	if (wordscpy(result, s, c))
// 		return (NULL);
// 	return (result);
// }
