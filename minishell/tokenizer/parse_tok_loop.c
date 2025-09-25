/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tok_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:27:01 by skuik             #+#    #+#             */
/*   Updated: 2025/09/25 11:08:11 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_token_loop(t_token *tok, t_cmd_builder *b)
{
	while (tok && tok->type != T_PIPE)
	{
		handle_token(tok, b);
		if ((tok->type >= T_REDIR_IN && tok->type <= T_REDIR_HEREDOC)
			&& tok->next)
			tok = tok->next;
		tok = tok->next;
	}
}

static void	process_word_token(t_token *tok, t_cmd_builder *b, env_t *env,
	bool *is_first)
{
	char	*value;

	if (!tok || !b)
		return ;
	value = get_token_value(tok, env);
	if (!value)
		return ;
	if (*is_first)
	{
		b->cmd->command = value;
		*is_first = false;
	}
	else
		list_add_back(&b->args, value);
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
			tok = tok->next;
	}
	return (true);
}

void	finalize_cmd_builder(t_cmd_builder *b, t_command **out)
{
	if (!b->cmd->command)
		b->cmd->command = ft_strdup("");
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
