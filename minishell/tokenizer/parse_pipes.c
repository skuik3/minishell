/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:59:49 by skuik             #+#    #+#             */
/*   Updated: 2025/09/11 09:02:30 by skuik            ###   ########.fr       */
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

bool	init_commands(t_command **head, t_token *tokens)
{
	t_command *tail = NULL;
	t_command *cmd = NULL;

	while (tokens)
	{
		t_token *segment = tokens, *end = NULL;
		find_segment_end(&end, tokens);
		if (end && end->next)
		{
			tokens = end->next->next;
			end->next = NULL;
		}
		else
			tokens = NULL;
		if (!parse_tokens(segment, &cmd))
			return (false);
		cmd->next = NULL;
		if (!(*head))
			*head = cmd;
		else
			tail->next = cmd;
		tail = cmd;
	}
	return (true);
}
