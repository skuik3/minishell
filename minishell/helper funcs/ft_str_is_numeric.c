/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:40:24 by skuik             #+#    #+#             */
/*   Updated: 2023/09/27 13:29:20 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

int	ft_str_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			return (0);
		}
		i++;
	}
	return (1);
}
// int	main(void)
// {
// 	char str1[] = "HelloWorld45";
// 	char str2[] = "3333333";

// 	int result1 = ft_str_is_numeric(str1);
// 	int result2 = ft_str_is_numeric(str2);

// 	printf("Justnumbers: %d\n", result1);
// 	printf("Justnumbers: %d\n", result2);

// 	return 0;
// }