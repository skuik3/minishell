/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:59:49 by skuik             #+#    #+#             */
/*   Updated: 2025/09/18 20:24:06 by skuik            ###   ########.fr       */
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

bool	init_commands(t_command **head, t_token *tokens, env_t *env)
{
	t_command *tail = NULL;
	t_command *cmd = NULL;

	*head = NULL;
	while (tokens)
	{
		t_token *segment = tokens, *end = NULL;
		t_token *saved_next = NULL;
		
		find_segment_end(&end, tokens);
		if (end && end->next)
		{
			tokens = end->next->next;
			saved_next = end->next;
			end->next = NULL;
		}
		else
			tokens = NULL;
			
		if (!parse_tokens(segment, &cmd, env))
		{
			if (saved_next)
				end->next = saved_next;
			if (*head)
				free_cmd(*head);
			return (false);
		}
		if (saved_next)
			end->next = saved_next;
			
		cmd->next = NULL;
		if (!(*head))
			*head = cmd;
		else
			tail->next = cmd;
		tail = cmd;
	}
	return (true);
}
