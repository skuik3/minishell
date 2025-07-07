/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:52:24 by skuik             #+#    #+#             */
/*   Updated: 2023/10/23 09:44:09 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*needle)
	{
		return ((char *)haystack);
	}
	while (haystack[i] && i < n)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < n && needle [j])
		{
			j++;
		}
		if (!needle[j])
		{
			return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
