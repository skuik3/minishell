/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:40:18 by skuik             #+#    #+#             */
/*   Updated: 2023/09/27 13:28:58 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

int	ft_str_is_alpha(char *str)
{
	while (*str)
	{
		if ((*str < 'A' || *str > 'Z')
			&& (*str < 'a' || *str > 'z'))
			return (0);
		++str;
	}
	return (1);
}
// int	main(void)
// {
// 	char str1[] = "HelloWorld";
// 	char str2[] = "123abc";

// 	int result1 = ft_str_is_alpha(str1);
// 	int result2 = ft_str_is_alpha(str2);

// 	printf("ABCo: %d\n", result1);
// 	printf("ABCo: %d\n", result2);

// 	return 0;
// }