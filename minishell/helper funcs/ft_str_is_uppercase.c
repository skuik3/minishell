/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:40:33 by skuik             #+#    #+#             */
/*   Updated: 2023/09/27 13:29:42 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

int	ft_str_is_uppercase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 'A' && str[i] <= 'Z'))
			return (0);
		i++;
	}
	return (1);
}
// int main(void)
// {
//     char str1[] = "HelloWorld";
//     char str2[] = "ANYADAT";

//     int result1 = ft_str_is_uppercase(str1);
//     int result2 = ft_str_is_uppercase(str2);

//     printf("Onlyup: %d\n", result1);
//     printf("Onlyup: %d\n", result2);

//     return 0;
// }