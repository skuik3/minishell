/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tok_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:27:01 by skuik             #+#    #+#             */
/*   Updated: 2025/09/11 22:37:53 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*new_redir(t_token *tok, t_redir_type type)
{
	t_redir *r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->filename = strdup(tok->value);
	r->type = type;
	return (r);
}

void	add_redir_token(t_token *tok, t_cmd_builder *b)
{
	t_redir *r;

	if (!tok->next)
		return;

	if (tok->type == T_REDIR_IN || tok->type == T_REDIR_HEREDOC)
		r = new_redir(tok->next, 
			tok->type == T_REDIR_IN ? REDIR_IN : REDIR_HEREDOC);
	else if (tok->type == T_REDIR_OUT || tok->type == T_REDIR_APPEND)
		r = new_redir(tok->next,
			tok->type == T_REDIR_OUT ? REDIR_OUT : REDIR_APPEND);
	else
		return;

	if (r)
	{
		if (tok->type == T_REDIR_IN || tok->type == T_REDIR_HEREDOC)
			list_add_back(&b->redir_in, r);
		else
			list_add_back(&b->redir_out, r);
	}
}


void	list_add_back(t_list **list, void *content)
{
	t_list *new_node = malloc(sizeof(t_list));
	t_list *temp;

	if (!new_node)
		return;
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

static int list_size(t_list *list)
{
	int count = 0;

	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

static char **alloc_str_array(t_list *list, int count)
{
	char **arr = malloc(sizeof(char *) * (count + 1));
	int i;

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

static t_redir **alloc_redir_array(t_list *list, int count)
{
	t_redir **arr = malloc(sizeof(t_redir *) * (count + 1));
	int i;

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

static char **list_to_str_array(t_list *list)
{
	int count = list_size(list);

	if (count == 0)
		return (NULL);
	return (alloc_str_array(list, count));
}

static t_redir **list_to_redir_array(t_list *list)
{
	int count = list_size(list);

	if (count == 0)
		return (NULL);
	return (alloc_redir_array(list, count));
}

static bool is_invalid_token(t_token *tok)
{
	if (!tok)
		return (true);
	if (tok->type == T_PIPE && (!tok->next || tok->next->type != T_WORD))
		return (true);
	if (tok->type == T_REDIR_IN && (!tok->next || tok->next->type != T_WORD))
		return (true);
	if (tok->type == T_REDIR_OUT && (!tok->next || tok->next->type != T_WORD))
		return (true);
	if (tok->type == T_REDIR_HEREDOC && (!tok->next || tok->next->type != T_WORD))
		return (true);
	if (tok->type == T_REDIR_APPEND && (!tok->next || tok->next->type != T_WORD))
		return (true);
	return (false);
}

static void parse_token_loop(t_token *tok, t_cmd_builder *b)
{
	while (tok && tok->type != T_PIPE)
	{
		handle_token(tok, b);
		if ((tok->type >= T_REDIR_IN && tok->type <= T_REDIR_HEREDOC) && tok->next)
			tok = tok->next;
		tok = tok->next;
	}
}

bool	init_cmd_builder(t_cmd_builder *b, t_command **out)
{
	*out = NULL;
	b->cmd = malloc(sizeof(t_command));
	if (!b->cmd)
		return (false);
	memset(b->cmd, 0, sizeof(t_command));
	b->args = NULL;
	b->redir_in = NULL;
	b->redir_out = NULL;
	return (true);
}


bool	process_tokens(t_token *tok, t_cmd_builder *b)
{
	bool is_first_token = true;

	while (tok)
	{
		if (tok->type >= T_REDIR_IN && tok->type <= T_REDIR_HEREDOC)
		{
			add_redir_token(tok, b);
			tok = tok->next;
		}
		else if (tok->type == T_WORD)
		{
			if (is_first_token)
			{
				b->cmd->command = strdup(tok->value);
				is_first_token = false;
			}
			else
				list_add_back(&b->args, strdup(tok->value));
		}
		tok = tok->next;
	}
	return (true);
}

void	finalize_cmd_builder(t_cmd_builder *b, t_command **out)
{
	b->cmd->arguments = list_to_str_array(b->args);
	b->cmd->arg_count = list_size(b->args);

	b->cmd->redir_in = list_to_redir_array(b->redir_in);
	b->cmd->redir_in_count = list_size(b->redir_in);

	b->cmd->redir_out = list_to_redir_array(b->redir_out);
	b->cmd->redir_out_count = list_size(b->redir_out);

	*out = b->cmd;
}


bool	parse_tokens(t_token *tok, t_command **out)
{
	t_cmd_builder b;

	if (is_invalid_token(tok))
		return (false);
	if (!init_cmd_builder(&b, out))
		return (false);
	if (!process_tokens(tok, &b))
		return (false);
	finalize_cmd_builder(&b, out);
	return (true);
}
