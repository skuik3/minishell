/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:52:12 by skuik             #+#    #+#             */
/*   Updated: 2023/10/23 12:03:51 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	l1;
	unsigned int	l2;
	unsigned int	s;

	l1 = ft_strlen(dst);
	l2 = ft_strlen(src);
	s = 0;
	if (size <= l1)
		return (l2 + size);
	while (l1 + s < size - 1)
	{
		dst[l1 + s] = src[s];
		s++;
	}
	dst[l1 + s] = '\0';
	return (l1 + l2);
}
