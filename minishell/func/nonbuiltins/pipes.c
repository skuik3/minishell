/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:57:39 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/25 10:10:31 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int counting_pipes(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd->next != NULL)
	{
		cmd = cmd->next;
		count++;
	}
	return (count);
}

t_pipe *adding_pipe(t_pipe *pipe_cmd)
{
	t_pipe	*new;

	new = malloc(sizeof(t_pipe));
	if (new == NULL)
	{
		perror("");
		return (NULL);
	}
	new->pipe = malloc(sizeof(int) * 2);
	if (new->pipe == NULL)
	{
		perror("");
		return (NULL);
	}
	new->next = NULL;
	while (pipe_cmd->next != NULL)
		pipe_cmd = pipe_cmd->next;
	pipe_cmd->next = new;
	return(pipe_cmd);
}

t_pipe *creating_first_pipe(void)
{
	t_pipe	*pipe_cmd;

	pipe_cmd = malloc(sizeof(t_pipe));
	if (pipe_cmd == NULL)
	{
		perror("");
		return (NULL);
	}
	pipe_cmd->pipe = malloc(sizeof(int) * 2);
	if (pipe_cmd->pipe == NULL)
	{
		perror("");
		return (NULL);
	}
	pipe_cmd->next = NULL;
	return (pipe_cmd);
}

t_pipe *prepare_pipes(t_command *cmd)
{
	int		pipe_count;
	t_pipe	*pipe_cmd;
	t_pipe	*head;
	int		i;

	pipe_count = counting_pipes(cmd);
	i = 0;
	pipe_cmd = creating_first_pipe();
	head = pipe_cmd;
	while (i < pipe_count - 1)
	{
		pipe_cmd = adding_pipe(pipe_cmd);
		i++;
	}
	pipe_cmd = head;
	while (pipe_cmd != NULL)
	{
		if (pipe(pipe_cmd->pipe))
		{
			perror("");
			return (NULL);
		}
		pipe_cmd = pipe_cmd->next;
	}
	return(head);
}
