/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:24:13 by skuik             #+#    #+#             */
/*   Updated: 2025/09/24 14:53:07 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*current;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

static char	*get_filename_from_token(t_token *tok)
{
	if (tok->next)
		return (strdup(tok->next->value));
	return (strdup(""));
}

static void	handle_redir_token(t_token *tok, t_cmd_builder *b)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return ;
	redir->filename = get_filename_from_token(tok);
	if (tok->type == T_REDIR_IN)
		redir->type = REDIR_IN;
	else if (tok->type == T_REDIR_OUT)
		redir->type = REDIR_OUT;
	else if (tok->type == T_REDIR_APPEND)
		redir->type = REDIR_APPEND;
	else if (tok->type == T_REDIR_HEREDOC)
		redir->type = REDIR_HEREDOC;
	if (tok->type == T_REDIR_IN || tok->type == T_REDIR_HEREDOC)
		lstadd_back(&b->redir_in, lstnew(redir));
	else
		lstadd_back(&b->redir_out, lstnew(redir));
	if (tok->type == T_REDIR_HEREDOC && tok->next)
		b->cmd->command = strdup(tok->next->value);
}

void	handle_token(t_token *tok, t_cmd_builder *b)
{
	if (tok->type == T_WORD)
	{
		if (!b->cmd->command)
			b->cmd->command = strdup(tok->value);
		lstadd_back(&b->args, lstnew(strdup(tok->value)));
	}
	else if (tok->type >= T_REDIR_IN && tok->type <= T_REDIR_HEREDOC)
	{
		handle_redir_token(tok, b);
	}
}
