/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:51:39 by skuik             #+#    #+#             */
/*   Updated: 2023/10/23 11:20:41 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (!dest && !src)
	{
		return (NULL);
	}
	d = (char *)dest;
	s = (const char *)src;
	while (n > 0)
	{
		*(d++) = *(s++);
		n--;
	}
	return (dest);
}
