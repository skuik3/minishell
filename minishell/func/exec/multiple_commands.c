/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:57:51 by ahavrank          #+#    #+#             */
/*   Updated: 2025/09/26 20:58:39 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_before_multiple(t_biggie *bigs)
{
	bigs->exit_status = check_heredoc(bigs);
	if (bigs->exit_status == 1)
	{
		perror("");
		return (1);
	}
	if (bigs->exit_status == SIGINT)
		return (130);
	return (0);
}

int	multiple_child_loop(t_biggie *bigs)
{
	int	status;

	status = 0;
	signal(SIGINT, SIG_DFL);
	if (bigs->cmd->is_first == 1)
	{
		status = first_multiple(bigs);
		if (status != 0)
		{
			free_big(bigs);
			exit (status);
		}
	}
	else
		status = other_multiple(bigs);
	free_big(bigs);
	exit(status);
}

int	multiple_cnt(t_biggie *bigs)
{
	int	pid;
	int	status;

	status = 0;
	while (bigs->cmd->next != NULL && g_signal != SIGINT)
	{
		signal(SIGINT, handle_signal_child);
		pid = fork();
		if (pid < -1)
			return (perror(""), 1);
		else if (pid == 0)
			multiple_child_loop(bigs);
		if (bigs->cmd->is_first == 1)
			close(bigs->pipe_cmd->pipe[1]);
		else
		{
			close(bigs->pipe_cmd->pipe[0]);
			close(bigs->pipe_cmd->next->pipe[1]);
			bigs->pipe_cmd = bigs->pipe_cmd->next;
		}
		if (bigs->cmd->redir_in != NULL)
			close_herepipe(bigs->cmd);
		bigs->cmd = bigs->cmd->next;
	}
	return (status);
}

int	multiple_commands(t_biggie *bigs)
{
	int	orig_stdout;
	int	orig_stdin;

	orig_stdout = dup(STDOUT_FILENO);
	orig_stdin = dup(STDIN_FILENO);
	if (orig_stdout == -1 || orig_stdin == -1)
	{
		perror("");
		return (1);
	}
	put_orig(bigs, orig_stdin, orig_stdout);
	bigs->exit_status = check_before_multiple(bigs);
	if (bigs->exit_status != 0)
		return (bigs->exit_status);
	bigs->exit_status = multiple_cnt(bigs);
	if (g_signal != SIGINT)
		bigs->exit_status = last_multiple(bigs);
	if (bigs->cmd->redir_in != NULL)
		close_herepipe(bigs->cmd);
	return (bigs->exit_status);
}
