/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:27:01 by skuik             #+#    #+#             */
/*   Updated: 2025/09/24 17:29:47 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_redir_to_list(t_token *tok, t_redir *r, t_cmd_builder *b)
{
	if (tok->type == T_REDIR_IN || tok->type == T_REDIR_HEREDOC)
		list_add_back(&b->redir_in, r);
	else
		list_add_back(&b->redir_out, r);
}

void	list_add_back(t_list **list, void *content)
{
	t_list	*new_node;
	t_list	*temp;

	if (!list || !content)
		return ;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = content;
	new_node->next = NULL;
	if (!*list)
		*list = new_node;
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

int	list_size(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

char	**list_to_str_array(t_list *list)
{
	int	count;

	count = list_size(list);
	if (count == 0)
		return (NULL);
	return (alloc_str_array(list, count));
}

t_redir	**list_to_redir_array(t_list *list)
{
	int	count;

	count = list_size(list);
	if (count == 0)
		return (NULL);
	return (alloc_redir_array(list, count));
}
