/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:23:33 by skuik             #+#    #+#             */
/*   Updated: 2025/02/11 14:36:51 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	f_nline(t_list_gnl *list_gnl)
{
	int	i;

	if (NULL == list_gnl)
		return (0);
	while (list_gnl)
	{
		i = 0;
		while (list_gnl->str_buf_g[i] && i < BUFFER_SIZE)
		{
			if (list_gnl->str_buf_g[i] == '\n')
				return (1);
			++i;
		}
		list_gnl = list_gnl->next_gnl;
	}
	return (0);
}

t_list_gnl	*f_last_node(t_list_gnl *list_gnl)
{
	if (NULL == list_gnl)
		return (NULL);
	while (list_gnl->next_gnl)
		list_gnl = list_gnl->next_gnl;
	return (list_gnl);
}

void	copy_str(t_list_gnl *list_gnl, char *str)
{
	int	i;
	int	k;

	if (NULL == list_gnl)
		return ;
	k = 0;
	while (list_gnl)
	{
		i = 0;
		while (list_gnl->str_buf_g[i] != 0)
		{
			if (list_gnl->str_buf_g[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list_gnl->str_buf_g[i++];
		}
		list_gnl = list_gnl->next_gnl;
	}
	str[k] = '\0';
}

int	len_to_nline(t_list_gnl *list_gnl)
{
	int	i;
	int	len;

	if (NULL == list_gnl)
		return (0);
	len = 0;
	while (list_gnl)
	{
		i = 0;
		while (list_gnl->str_buf_g[i] != 0)
		{
			if (list_gnl->str_buf_g[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list_gnl = list_gnl->next_gnl;
	}
	return (len);
}

void	dealloc(t_list_gnl **list_gnl, t_list_gnl *clean_node, char *buf)
{
	t_list_gnl	*tmp;

	if (NULL == *list_gnl)
		return ;
	while (*list_gnl)
	{
		tmp = (*list_gnl)->next_gnl;
		free((*list_gnl)->str_buf_g);
		free(*list_gnl);
		*list_gnl = tmp;
	}
	*list_gnl = NULL;
	if (clean_node->str_buf_g[0])
		*list_gnl = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}
