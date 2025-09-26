/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:03:31 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/26 20:52:01 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_redirect(t_command *cmd)
{
	int	returned;

	returned = 0;
	if (cmd->redir_in != NULL)
	{
		returned = redirect_in(cmd);
		if (returned == 1)
			return (1);
	}
	if (cmd->redir_out != NULL)
	{
		returned = redirect_out(cmd);
		if (returned == 1)
			return (1);
	}
	return (returned);
}

int	redirecting_out(t_redir *redirout)
{
	int	fd;

	if (access(redirout->filename, W_OK) == 0)
	{
		if (unlink(redirout->filename) == -1)
			return (1);
	}
	fd = open(redirout->filename, O_RDWR | O_CREAT, SHELL_DEFAULT);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	appending(t_redir *append)
{
	int	fd;

	if (access(append->filename, W_OK) == 0)
		return (0);
	fd = open(append->filename, O_RDWR | O_CREAT, SHELL_DEFAULT);
	if (fd == -1)
		return (1);
	close (fd);
	return (0);
}

int	last_redirect_out(t_redir *last)
{
	int	fd;

	if (last->type == REDIR_OUT)
	{
		if (access(last->filename, W_OK) == 0)
		{
			if (unlink(last->filename) == -1)
				return (1);
		}
	}
	fd = open(last->filename, O_RDWR | O_CREAT | O_APPEND, SHELL_DEFAULT);
	if (fd == -1)
		return (1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (1);
	close(fd);
	return (0);
}

int	redirect_out(t_command *cmd)
{
	int	i;
	int	returned;

	i = 0;
	returned = 0;
	while (cmd->redir_out[i + 1] != NULL)
	{
		if (cmd->redir_out[i]->type == REDIR_OUT)
			returned = redirecting_out(cmd->redir_out[i]);
		else if (cmd->redir_out[i]->type == REDIR_APPEND)
			returned = appending(cmd->redir_out[i]);
		i++;
	}
	returned = last_redirect_out(cmd->redir_out[i]);
	return (returned);
}
