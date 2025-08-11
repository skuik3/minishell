/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 09:47:51 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/08/11 09:53:37 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*temp;
// 	int		i;
// 	int		k;

// 	temp = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
// 	if (temp == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i] != '\0')
// 	{
// 		temp[i] = s1[i];
// 		i++;
// 	}
// 	k = 0;
// 	while (s2[k] != '\0')
// 	{
// 		temp[i] = s2[k];
// 		k++;
// 		i++;
// 	}
// 	temp[i] = '\0';
// 	return (temp);
// }

char	*ft_strdup(const char *s1)
{
	char				*temp;
	unsigned int		i;

	temp = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}