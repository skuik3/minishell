/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:10:06 by skuik             #+#    #+#             */
/*   Updated: 2023/09/27 13:29:29 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

int	ft_str_is_printable(char *str)
{
	while (*str != '\0')
	{
		if (!(*str >= 32 && *str <= 126))
			return (0);
		str++;
	}
	return (1);
}
// int main(void)
// {
//     char str1[] = "HelloWorld655615";
//     char str2[] = "123abc";

//     int result1 = ft_str_is_printable(str1);
//     int result2 = ft_str_is_printable(str2);

//     printf("Printable: %d\n", result1);
//     printf("Printable: %d\n", result2);

//     return 0;
// }