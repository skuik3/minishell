/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_and_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:42:31 by skuik             #+#    #+#             */
/*   Updated: 2025/09/25 10:58:05 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	handle_pipe_and_end_tokens(t_token *curr, bool expecting_cmd)
{
	if (curr->type == T_PIPE)
	{
		if (expecting_cmd)
		{
			printf("syntax error near unexpected token `|'\n");
			return (false);
		}
	}
	else if (curr->type == T_END)
	{
		if (expecting_cmd)
		{
			printf("syntax error near unexpected token `;'\n");
			return (false);
		}
	}
	return (true);
}

bool	handle_redirection_tokens(t_token *curr)
{
	if (!curr->next || curr->next->type != T_WORD)
	{
		if (curr->type == T_REDIR_HEREDOC)
			printf("syntax error near unexpected token `<<'\n");
		else if (curr->type == T_REDIR_APPEND)
			printf("syntax error near unexpected token `>>'\n");
		else if (curr->type == T_REDIR_OUT)
			printf("syntax error near unexpected token `>'\n");
		else if (curr->type == T_REDIR_IN)
			printf("syntax error near unexpected token `<'\n");
		return (false);
	}
	return (true);
}

static bool	handle_final_token_check(t_token *tokens, bool expecting_cmd)
{
	t_token	*curr;

	if (expecting_cmd && tokens)
	{
		curr = tokens;
		while (curr->next)
			curr = curr->next;
		if (curr->type == T_PIPE)
			printf("syntax error near unexpected token `|'\n");
		else if (curr->type == T_END)
			printf("syntax error near unexpected token `;'\n");
		else
			printf("syntax error near unexpected token\n");
		return (false);
	}
	return (true);
}

bool	validate_syntax(t_token *tokens)
{
	t_token	*curr;
	bool	expecting_cmd;

	curr = tokens;
	expecting_cmd = true;
	while (curr)
	{
		if (curr->type == T_PIPE || curr->type == T_END)
		{
			if (!handle_pipe_and_end_tokens(curr, expecting_cmd))
				return (false);
			expecting_cmd = true;
		}
		else if (curr->type >= T_REDIR_IN && curr->type <= T_REDIR_HEREDOC)
		{
			if (!handle_redirection_tokens(curr))
				return (false);
			expecting_cmd = false;
			curr = curr->next;
		}
		else if (curr->type == T_WORD)
			expecting_cmd = false;
		curr = curr->next;
	}
	return (handle_final_token_check(tokens, expecting_cmd));
}
