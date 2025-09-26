/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:56:25 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/26 21:08:15 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	first_multiple(t_biggie *bigs)
{
	if (bigs->cmd->redir_in != NULL || bigs->cmd->redir_out != NULL)
	{
		if (check_redirect(bigs->cmd) == 1)
		{
			perror("");
			free_big(bigs);
			exit(1);
		}
	}
	if (bigs->cmd->redir_out == NULL)
	{
		if (dup2(bigs->pipe_cmd->pipe[1], STDOUT_FILENO) == -1)
			return (perror(""), 1);
	}
	close(bigs->pipe_cmd->pipe[0]);
	close(bigs->pipe_cmd->pipe[1]);
	close_pipes(bigs);
	if (is_builtint(bigs->cmd->command) == 0)
		bigs->exit_status = what_builtin(bigs);
	else if (is_builtint(bigs->cmd->command) == 1)
		bigs->exit_status = executing(bigs->cmd);
	return (bigs->exit_status);
}

int	check_other_multiple(t_biggie *bigs)
{
	if (bigs->cmd->redir_in != NULL || bigs->cmd->redir_out != NULL)
	{
		if (check_redirect(bigs->cmd) == 1)
		{
			perror("");
			free_big(bigs);
			exit(1);
		}
	}
	if (bigs->cmd->redir_in == NULL)
	{
		if (dup2(bigs->pipe_cmd->pipe[0], STDIN_FILENO) == -1)
		{
			perror("");
			return (1);
		}
	}
	return (0);
}

int	other_multiple(t_biggie *bigs)
{
	if (check_other_multiple(bigs) != 0)
		return (1);
	close(bigs->pipe_cmd->pipe[0]);
	if (bigs->cmd->redir_out == NULL)
	{
		if (dup2(bigs->pipe_cmd->next->pipe[1], STDOUT_FILENO) == -1)
		{
			perror("");
			return (1);
		}
	}
	close(bigs->pipe_cmd->next->pipe[0]);
	close(bigs->pipe_cmd->next->pipe[1]);
	close_pipes(bigs);
	if (is_builtint(bigs->cmd->command) == 0)
		bigs->exit_status = what_builtin(bigs);
	else if (is_builtint(bigs->cmd->command) == 1)
		bigs->exit_status = executing(bigs->cmd);
	return (bigs->exit_status);
}

void	close_pipes(t_biggie *bigs)
{
	while (bigs->pipe_cmd != NULL)
	{
		close(bigs->pipe_cmd->pipe[0]);
		close(bigs->pipe_cmd->pipe[1]);
		bigs->pipe_cmd = bigs->pipe_cmd->next;
	}
}
