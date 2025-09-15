/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftrtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:39:47 by skuik             #+#    #+#             */
/*   Updated: 2023/10/23 09:45:21 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;

	if (s1 == NULL || set == NULL)
	{
		return (NULL);
	}
	i = 0;
	j = ft_strlen((char *)s1);
	while (ft_strchr(set, s1[i]))
	{
		i++;
	}
	while (j > i && ft_strchr(set, s1[j]))
	{
		j--;
	}
	return (ft_substr(s1, i, j - i + 1));
}
