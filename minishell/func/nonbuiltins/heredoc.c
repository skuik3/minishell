/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:03:31 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/26 01:48:19 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	last_heredoc(t_biggie *bigs, int i)
{
	int		pid;
	t_redir	*last;
	int		status;

	last = bigs->cmd->redir_in[i];
	last->pipe_forhdc = malloc(sizeof(int) * 2);
	if (last->pipe_forhdc == NULL)
		return (1);
	if (pipe(last->pipe_forhdc) == -1)
		return (1);
	signal(SIGINT, handle_signal_child);
	pid = fork();
	if (pid < -1)
		return (1);
	else if (pid == 0)
		child_heredoc(bigs, i);
	close(last->pipe_forhdc[1]);
	waitpid(pid, &status, 0);
	bigs->exit_status = WEXITSTATUS(status);
	if (g_signal == SIGINT)
	{
		close(last->pipe_forhdc[0]);
		return (SIGINT);
	}
	return (bigs->exit_status);
}

int	redirecting_heredoc(t_biggie *bigs, int i)
{
	char				*promt;
	int					pid;
	int					status;
	t_redir				*heredoc;
	struct sigaction	sa;

	heredoc = bigs->cmd->redir_in[i];
	signal(SIGINT, handle_signal_child);
	pid = fork();
	if (pid < -1)
		return (1);
	else if (pid == 0)
	{
		set_ctrl(sa);
		promt = get_line_heredoc(heredoc);
		free(promt);
		free_big(bigs);
		exit(0);
	}
	if (g_signal == SIGINT)
		return (SIGINT);
	waitpid(pid, &status, 0);
	return (status);
}

int	setting_pipe_hdc(t_biggie *bigs)
{
	int	i;

	i = 0;
	while (bigs->cmd->redir_in[i] != NULL)
	{
		if (bigs->cmd->redir_in[i]->type == REDIR_HEREDOC)
			bigs->cmd->redir_in[i]->pipe_forhdc = NULL;
		i++;
	}
	return (0);
}

int	do_heredoc(t_biggie *bigs)
{
	int	i;
	int	returned;

	i = 0;
	returned = 0;
	setting_pipe_hdc(bigs);
	while (bigs->cmd->redir_in[i + 1] != NULL)
	{
		if (bigs->cmd->redir_in[i]->type == REDIR_HEREDOC)
			returned = redirecting_heredoc(bigs, i);
		if (returned == SIGINT)
			return (returned);
		i++;
	}
	while (bigs->cmd->redir_in[i] != NULL)
	{
		if (bigs->cmd->redir_in[i]->type == REDIR_HEREDOC)
			returned = last_heredoc(bigs, i);
		i++;
	}
	return (returned);
}

int	check_heredoc(t_biggie *bigs)
{
	int			returned;
	t_command	*head;

	returned = 0;
	head = bigs->cmd;
	if (bigs->cmd->next == NULL && bigs->cmd->is_first == 1)
	{
		if (heredoc_present(bigs->cmd->redir_in) == 1)
			returned = do_heredoc(bigs);
		return (returned);
	}
	while (bigs->cmd != NULL)
	{
		if (heredoc_present(bigs->cmd->redir_in) == 1)
			returned = do_heredoc_multiple(bigs);
		if (returned == SIGINT)
			return (returned);
		bigs->cmd = bigs->cmd->next;
	}
	bigs->cmd = head;
	return (returned);
}
