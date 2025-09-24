/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tok_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:27:01 by skuik             #+#    #+#             */
/*   Updated: 2025/09/24 14:28:23 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*new_redir(t_token *tok, t_redir_type type)
{
	t_redir	*r;

	if (!tok)
		return (NULL);
	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->filename = strdup(tok->value);
	if (!r->filename)
	{
		free(r);
		return (NULL);
	}
	r->type = type;
	r->pipe_forhdc = NULL;
	r->position = 0;
	return (r);
}

static	t_redir_type	get_redir_type_from_token(t_token_type tok_type)
{
	if (tok_type == T_REDIR_IN)
		return (REDIR_IN);
	if (tok_type == T_REDIR_HEREDOC)
		return (REDIR_HEREDOC);
	if (tok_type == T_REDIR_OUT)
		return (REDIR_OUT);
	if (tok_type == T_REDIR_APPEND)
		return (REDIR_APPEND);
	return (REDIR_IN);
}

static void	add_redir_to_list(t_token *tok, t_redir *r, t_cmd_builder *b)
{
	if (tok->type == T_REDIR_IN || tok->type == T_REDIR_HEREDOC)
		list_add_back(&b->redir_in, r);
	else
		list_add_back(&b->redir_out, r);
}

void	add_redir_token(t_token *tok, t_cmd_builder *b)
{
	t_redir	*r;

	if (!tok->next)
		return ;
	if (tok->type == T_REDIR_IN || tok->type == T_REDIR_HEREDOC)
		r = new_redir(tok->next, get_redir_type_from_token(tok->type));
	else if (tok->type == T_REDIR_OUT || tok->type == T_REDIR_APPEND)
		r = new_redir(tok->next, get_redir_type_from_token(tok->type));
	else
		return ;
	if (r)
		add_redir_to_list(tok, r, b);
}

void	list_add_back(t_list **list, void *content)
{
	t_list	*new_node;
	t_list	*temp;

	if (!list || !content)
		return;
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

static int	list_size(t_list *list)
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

static char	**list_to_str_array(t_list *list)
{
	int	count = list_size(list);

	if (count == 0)
		return (NULL);
	return (alloc_str_array(list, count));
}

static t_redir	**list_to_redir_array(t_list *list)
{
	int count = list_size(list);

	if (count == 0)
		return (NULL);
	return (alloc_redir_array(list, count));
}

static bool	is_invalid_token(t_token *tok)
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

void	parse_token_loop(t_token *tok, t_cmd_builder *b)
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

static char	*get_token_value(t_token *tok, env_t *env)
{
	(void)env;
	if (!tok || !tok->value)
		return (strdup(""));
	return (strdup(tok->value));
}

static void	process_word_token(t_token *tok, t_cmd_builder *b, env_t *env, bool *is_first)
{
	char	*value;

	if (!tok || !b)
		return;
	value = get_token_value(tok, env);
	if (!value)
		return;
	if (*is_first)
	{
		b->cmd->command = value;
		*is_first = false;
	}
	else
	{
		list_add_back(&b->args, value);
	}
}

bool	process_tokens(t_token *tok, t_cmd_builder *b, env_t *env)
{
	bool	is_first_token;

	is_first_token = true;
	while (tok)
	{
		if (tok->type >= T_REDIR_IN && tok->type <= T_REDIR_HEREDOC)
		{
			add_redir_token(tok, b);
			tok = tok->next;
			if (tok)
				tok = tok->next;
		}
		else if (tok->type == T_WORD)
		{
			process_word_token(tok, b, env, &is_first_token);
			tok = tok->next;
		}
		else
		{
			tok = tok->next;
		}
	}
	return (true);
}

void	finalize_cmd_builder(t_cmd_builder *b, t_command **out)
{
	if (!b->cmd->command)
		b->cmd->command = strdup("");
	b->cmd->arguments = list_to_str_array(b->args);
	b->cmd->redir_in = list_to_redir_array(b->redir_in);
	b->cmd->redir_in_count = list_size(b->redir_in);
	b->cmd->redir_out = list_to_redir_array(b->redir_out);
	b->cmd->redir_out_count = list_size(b->redir_out);
	*out = b->cmd;
}

bool	parse_tokens(t_token *tok, t_command **out, env_t *env)
{
	t_cmd_builder	b;

	if (is_invalid_token(tok))
		return (false);
	if (!init_cmd_builder(&b, out))
		return (false);
	if (!process_tokens(tok, &b, env))
	{
		if (b.cmd)
		{
			if (b.cmd->command)
				free(b.cmd->command);
			free(b.cmd);
		}
		free_string_list(b.args);
		free_list(b.redir_in);
		free_list(b.redir_out);
		return (false);
	}
	finalize_cmd_builder(&b, out);
	free_string_list(b.args);
	free_list(b.redir_in);
	free_list(b.redir_out);
	return (true);
}
