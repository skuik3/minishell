/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_pt2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:04:06 by ahavrank          #+#    #+#             */
/*   Updated: 2025/09/26 21:08:50 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	last_multiple_child(t_biggie *bigs)
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
			exit (1);
		}
	}
	close(bigs->pipe_cmd->pipe[1]);
	close_pipes(bigs);
	if (is_builtint(bigs->cmd->command) == 0)
		bigs->exit_status = what_builtin(bigs);
	else if (is_builtint(bigs->cmd->command) == 1)
		bigs->exit_status = executing(bigs->cmd);
	return (bigs->exit_status);
}

int	last_multiple(t_biggie *bigs)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid < -1)
	{
		perror("");
		return (1);
	}
	else if (pid == 0)
	{
		status = last_multiple_child(bigs);
		free_big(bigs);
		exit(status);
	}
	close(bigs->pipe_cmd->pipe[0]);
	waitpid(pid, &bigs->exit_status, 0);
	bigs->exit_status = WEXITSTATUS(bigs->exit_status);
	while (wait(&status) != -1)
		;
	if (bigs->exit_status == 2 || g_signal == SIGINT)
		bigs->exit_status = 130;
	return (bigs->exit_status);
}
