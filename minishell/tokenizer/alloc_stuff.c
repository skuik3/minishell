/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:27:01 by skuik             #+#    #+#             */
/*   Updated: 2025/09/19 18:20:26 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**alloc_str_array(t_list *list, int count)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (count + 1));
	i = 0;
	if (!arr)
		return (NULL);
	while (i < count)
	{
		arr[i] = strdup((char *)list->content);
		list = list->next;
		i++;
	}
	arr[count] = NULL;
	return (arr);
}

t_redir	**alloc_redir_array(t_list *list, int count)
{
	t_redir	**arr;
	int		i;

	arr = malloc(sizeof(t_redir *) * (count + 1));
	i = 0;
	if (!arr)
		return (NULL);
	while (i < count)
	{
		arr[i] = (t_redir *)list->content;
		list = list->next;
		i++;
	}
	arr[count] = NULL;
	return (arr);
}
