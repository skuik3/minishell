/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:38:13 by skuik             #+#    #+#             */
/*   Updated: 2023/10/23 10:54:22 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	long int	i;

	len = ft_numlen(n);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = n;
	if (n < 0)
	{
		str[0] = '-';
		i *= -1;
	}
	str[len] = '\0';
	len--;
	if (i == 0)
		str[0] = '0';
	while (i)
	{
		str[len] = i % 10 + '0';
		i /= 10;
		len--;
	}
	return (str);
}
