/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:03:31 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/25 18:27:17 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	where_last_heredoc(t_command *cmd, int rdhc)
{
	int	i;
	int	heredoc;
	int	redir;

	i = 0;
	redir = -1;
	heredoc = -1;
	while (cmd->redir_in[i] != NULL)
	{
		if (cmd->redir_in[i]->type == REDIR_IN)
			redir = i;
		else if (cmd->redir_in[i]->type == REDIR_HEREDOC)
			heredoc = i;
		i++;
	}
	if (rdhc == REDIR_IN)
		return (redir);
	else if (rdhc == REDIR_HEREDOC)
		return (heredoc);
	return (-1);
}

int	redirecting_in(t_redir *redirin)
{
	if (access(redirin->filename, R_OK) == -1)
		return (1);
	return (0);
}

//check if permission to write denied bahaviour
int	last_redirect_in(t_redir *last)
{
	int	fd;
	int	returned;

	returned = 0;
	if (access(last->filename, R_OK) == -1)
		return (1);
	fd = open(last->filename, O_RDWR | O_CREAT, SHELL_DEFAULT);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (1);
	close (fd);
	return (returned);
}

int	redirect_in(t_command *cmd)
{
	int	i;
	int	returned;

	i = 0;
	returned = 0;
	while (cmd->redir_in[i + 1] != NULL)
	{
		if (cmd->redir_in[i]->type == REDIR_IN)
			returned = redirecting_in(cmd->redir_in[i]);
		i++;
	}
	while (cmd->redir_in[i] != NULL)
	{
		if (cmd->redir_in[i]->type == REDIR_IN)
			returned = last_redirect_in(cmd->redir_in[i]);
		else {
			if (cmd->redir_in[i]->pipe_forhdc != NULL)
			{
				if (dup2(cmd->redir_in[i]->pipe_forhdc[0], STDIN_FILENO) == -1)
					return (1);
			}
			returned = 0;
		}
		i++;
	}
	return (returned);
}
