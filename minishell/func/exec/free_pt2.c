/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pt2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:21:21 by anezka            #+#    #+#             */
/*   Updated: 2025/09/27 14:05:32 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_arguments(char **arguments)
{
	int	i;

	i = 0;
	if (arguments == NULL)
		return ;
	while (arguments[i] != NULL)
	{
		free(arguments[i]);
		arguments[i] = NULL;
		i++;
	}
	free(arguments);
	arguments = NULL;
}

void	free_redir(t_redir **redir)
{
	int	i;

	i = 0;
	while (redir[i] != NULL)
	{
		free(redir[i]->filename);
		if (redir[i]->type == REDIR_HEREDOC)
		{
			free(redir[i]->pipe_forhdc);
			redir[i]->pipe_forhdc = NULL;
		}
		free(redir[i]);
		i++;
	}
	free(redir);
}

void	free_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->start[i] != NULL)
	{
		free(env->start[i]);
		i++;
	}
	free(env->start);
	i = 0;
	while (env->mod[i] != NULL)
	{
		free(env->mod[i]);
		i++;
	}
	free(env->mod);
	free(env);
}

void	free_commands(t_command *cmd)
{
	free(cmd->command);
	cmd->command = NULL;
	if (cmd->arguments != NULL)
		free_arguments(cmd->arguments);
	cmd->arguments = NULL;
	if (cmd->redir_in != NULL)
		free_redir(cmd->redir_in);
	cmd->redir_in = NULL;
	if (cmd->redir_out != NULL)
		free_redir(cmd->redir_out);
	cmd->redir_out = NULL;
}

void	free_pipes(t_pipe *pipe)
{
	free(pipe->pipe);
	pipe->pipe = NULL;
}
