/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_and_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:42:31 by skuik             #+#    #+#             */
/*   Updated: 2025/09/24 14:20:32 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	handle_pipe_and_end_tokens(t_token *current, bool expecting_cmd)
{
	if (current->type == T_PIPE)
	{
		if (expecting_cmd)
		{
			fprintf(stderr, "syntax error near unexpected token `|'\n");
			return (false);
		}
	}
	else if (current->type == T_END)
	{
		if (expecting_cmd)
		{
			fprintf(stderr, "syntax error near unexpected token `;'\n");
			return (false);
		}
	}
	return (true);
}

bool	handle_redirection_tokens(t_token *current)
{
	if (!current->next || current->next->type != T_WORD)
	{
		if (current->type == T_REDIR_HEREDOC)
			fprintf(stderr, "syntax error near unexpected token `<<'\n");
		else if (current->type == T_REDIR_APPEND)
			fprintf(stderr, "syntax error near unexpected token `>>'\n");
		else if (current->type == T_REDIR_OUT)
			fprintf(stderr, "syntax error near unexpected token `>'\n");
		else if (current->type == T_REDIR_IN)
			fprintf(stderr, "syntax error near unexpected token `<'\n");
		return (false);
	}
	return (true);
}

static bool	handle_final_token_check(t_token *tokens, bool expecting_cmd)
{
	t_token	*current;

	if (expecting_cmd && tokens)
	{
		current = tokens;
		while (current->next)
			current = current->next;
		if (current->type == T_PIPE)
			fprintf(stderr, "syntax error near unexpected token `|'\n");
		else if (current->type == T_END)
			fprintf(stderr, "syntax error near unexpected token `;'\n");
		else
			fprintf(stderr, "syntax error near unexpected token\n");
		return (false);
	}
	return (true);
}

bool	validate_syntax(t_token *tokens)
{
	t_token	*current;
	bool	expecting_cmd;

	current = tokens;
	expecting_cmd = true;
	while (current)
	{
		if (current->type == T_PIPE || current->type == T_END)
		{
			if (!handle_pipe_and_end_tokens(current, expecting_cmd))
				return (false);
			expecting_cmd = true;
		}
		else if (current->type >= T_REDIR_IN && current->type <= T_REDIR_HEREDOC)
		{
			if (!handle_redirection_tokens(current))
				return (false);
			expecting_cmd = false;
			current = current->next;
		}
		else if (current->type == T_WORD)
			expecting_cmd = false;
		current = current->next;
	}
	return (handle_final_token_check(tokens, expecting_cmd));
}
