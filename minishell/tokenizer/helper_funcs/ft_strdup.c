/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:35:58 by skuik             #+#    #+#             */
/*   Updated: 2023/10/23 09:39:13 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*rtn;
	size_t	len;

	len = ft_strlen(s1);
	rtn = malloc(sizeof(char) * (len + 1));
	if (!rtn)
		return (0);
	ft_strlcpy(rtn, s1, len + 1);
	return (rtn);
}
