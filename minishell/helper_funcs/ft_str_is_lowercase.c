/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:40:28 by skuik             #+#    #+#             */
/*   Updated: 2023/09/27 13:29:09 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

int	ft_str_is_lowercase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 'a' && str[i] <= 'z'))
		{
			return (0);
		}
		i++;
	}
	return (1);
}
// int main(void)
// {
//     char str1[] = "HahahhaH";
//     char str2[] = "jhjt";

//     int result1 = ft_str_is_lowercase(str1);
//     int result2 = ft_str_is_lowercase(str2);

//     printf("Lower: %d\n", result1);
//     printf("Lower: %d\n", result2);

//     return 0;
// }