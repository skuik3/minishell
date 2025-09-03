/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 09:47:51 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/03 11:30:12 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdup(const char *s1)
{
	char				*temp;
	unsigned int		i;

	temp = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (temp == NULL)
	{
		perror("");
        return (NULL);
	}
	i = 0;
	while (i < ft_strlen(s1))
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}