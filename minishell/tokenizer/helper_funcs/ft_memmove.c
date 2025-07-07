/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:51:47 by skuik             #+#    #+#             */
/*   Updated: 2025/02/13 17:06:50 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	hossz;

	hossz = 0;
	if (src < dest)
	{
		hossz = n;
		while (hossz > 0)
		{
			hossz--;
			((unsigned char *)dest)[hossz] = ((unsigned char *)src)[hossz];
		}
	}
	else
	{
		hossz = 0;
		while (hossz < n)
		{
			((unsigned char *)dest)[hossz] = ((unsigned char *)src)[hossz];
			hossz++;
		}
	}
	return (dest);
}
