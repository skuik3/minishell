/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:04:01 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/25 18:20:37 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_single_cmd(t_command *cmd)
{
	t_command	*current;

	while (cmd != NULL)
	{
		current = cmd;
		cmd = cmd->next;
		free_commands(current);
		free(current);
	}
}

void	free_big(t_biggie *bigs)
{
	t_pipe	*temp;

	if (bigs == NULL)
		return ;
	bigs->cmd = bigs->cmd_head;
	if (bigs->cmd != NULL)
		free_single_cmd(bigs->cmd);
	bigs->cmd = NULL;
	bigs->cmd_head = NULL;
	if (bigs->env != NULL)
		free_env(bigs->env);
	bigs->env = NULL;
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
	free(bigs);
	bigs = NULL;
}
