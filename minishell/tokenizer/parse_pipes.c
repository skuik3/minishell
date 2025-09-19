/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:59:49 by skuik             #+#    #+#             */
/*   Updated: 2025/09/19 17:26:24 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_segment_end(t_token **end, t_token *tokens)
{
	*end = NULL;
	while (tokens && tokens->type != T_PIPE)
	{
		*end = tokens;
		tokens = tokens->next;
	}
}

static bool	process_token_segment(t_token **tokens, t_command **cmd, env_t *env)
{
	t_token	*segment;
	t_token	*end;
	t_token	*saved_next;

	segment = *tokens;
	end = NULL;
	saved_next = NULL;
	find_segment_end(&end, *tokens);
	if (end && end->next)
	{
		*tokens = end->next->next;
		saved_next = end->next;
		end->next = NULL;
	}
	else
		*tokens = NULL;
	if (!parse_tokens(segment, cmd, env))
	{
		if (saved_next)
			end->next = saved_next;
		return (false);
	}
	if (saved_next)
		end->next = saved_next;
	return (true);
}

bool	init_commands(t_command **head, t_token *tokens, env_t *env)
{
	t_command	*tail;
	t_command	*cmd;

	*head = NULL;
	tail = NULL;
	while (tokens)
	{
		if (!process_token_segment(&tokens, &cmd, env))
		{
			if (*head)
				free_cmd(*head);
			return (false);
		}
		cmd->next = NULL;
		if (!(*head))
			*head = cmd;
		else
			tail->next = cmd;
		tail = cmd;
	}
	return (true);
}
