/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:44:46 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/25 18:44:48 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_biggie	*setting_big(void)
{
	t_biggie	*new;

	new = malloc(sizeof(t_biggie));
	if (new == NULL)
	{
		perror("");
		return (NULL);
	}
	new->cmd = NULL;
	new->cmd_head = NULL;
	new->env = NULL;
	new->exit_status = 0;
	new->pipe_cmd = NULL;
	new->pipe_head = NULL;
	return (new);
}

void	clean_big(t_biggie *bigs)
{
	t_command	*current;
	t_pipe		*temp;

	if (bigs == NULL)
		return ;
	bigs->cmd = bigs->cmd_head;
	while (bigs->cmd != NULL)
	{
		current = bigs->cmd;
		bigs->cmd = bigs->cmd->next;
		free_commands(current);
		free(current);
	}
	bigs->cmd = NULL;
	bigs->cmd_head = NULL;
	bigs->pipe_cmd = bigs->pipe_head;
	while (bigs->pipe_cmd != NULL)
	{
		temp = bigs->pipe_cmd;
		bigs->pipe_cmd = bigs->pipe_cmd->next;
		free_pipes(temp);
		free(temp);
	}
	bigs->pipe_cmd = NULL;
	bigs->pipe_head = NULL;
}
