/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/27 13:25:09 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	put_orig(t_biggie *bigs, int orig_stdin, int orig_stdout)
{
	while (bigs->cmd != NULL)
	{
		bigs->cmd->orig_stdin = orig_stdin;
		bigs->cmd->orig_stdout = orig_stdout;
		bigs->cmd = bigs->cmd->next;
	}
	bigs->cmd = bigs->cmd_head;
}

int	command_execution(t_biggie *bigs)
{
	t_command	*head;

	bigs->cmd->is_first = 1;
	if (bigs->cmd->next == NULL)
	{
		bigs->exit_status = single_command(bigs);
		return (bigs->exit_status);
	}
	bigs->pipe_cmd = prepare_pipes(bigs->cmd);
	bigs->pipe_head = bigs->pipe_cmd;
	head = bigs->cmd;
	while (bigs->cmd->next != NULL)
	{
		bigs->cmd = bigs->cmd->next;
		bigs->cmd->envar = bigs->env;
		bigs->cmd->is_first = 0;
	}
	bigs->cmd = head;
	bigs->exit_status = multiple_commands(bigs);
	return (bigs->exit_status);
}
