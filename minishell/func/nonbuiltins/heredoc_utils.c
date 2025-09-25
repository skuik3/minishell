/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:52:13 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/26 01:48:12 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_ctrl(struct sigaction sa)
{
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handle_signal_heredoc;
	sigaction(SIGINT, &sa, NULL);
}

int	child_heredoc(t_biggie *bigs, int i)
{
	t_redir				*last;
	char				*promt;
	char				*postpromt;
	struct sigaction	sa;

	last = bigs->cmd->redir_in[i];
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handle_signal_heredoc;
	sigaction(SIGINT, &sa, NULL);
	close(last->pipe_forhdc[0]);
	promt = get_line_heredoc(last);
	if (promt != NULL)
	{
		postpromt = expand_var(promt, bigs->env);
		write(last->pipe_forhdc[1], postpromt, ft_strlen(postpromt));
		free(postpromt);
	}
	close(last->pipe_forhdc[1]);
	free(promt);
	free_big(bigs);
	exit(0);
}

char	*get_line_heredoc(t_redir *last)
{
	char	*line;
	char	*returned;
	char	*cmp_line;

	returned = NULL;
	line = NULL;
	cmp_line = ft_strjoin(ft_strdup(last->filename), "\n");
	while (1 && g_signal != SIGINT)
	{
		write (STDOUT_FILENO, "> ", 3);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			free(cmp_line);
			free(returned);
			return (NULL);
		}
		if (ft_strcmp(line, cmp_line) == 0)
			break ;
		returned = ft_strjoin(returned, line);
		free(line);
	}
	free(cmp_line);
	free(line);
	return (returned);
}

int	heredoc_present(t_redir **redir)
{
	int	i;

	i = 0;
	if (redir == NULL)
		return (0);
	while (redir[i] != NULL)
	{
		if (redir[i]->type == REDIR_HEREDOC)
			return (1);
		i++;
	}
	return (0);
}

int	do_heredoc_multiple(t_biggie *bigs)
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
	if (bigs->cmd->redir_in[i]->type == REDIR_HEREDOC)
		returned = last_heredoc(bigs, i);
	return (returned);
}
