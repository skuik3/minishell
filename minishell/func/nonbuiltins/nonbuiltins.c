/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nonbuiltins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:27:14 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/25 13:42:10 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int executing_without_path(t_command *cmd, char **cmdw_args)
{
	char		*path;

	path = command_path(cmd);
	if (path == NULL)
	{
		ft_putstr_fd(cmd->command, 1);
		write(1, ": Command not found\n", 21);
		free_arguments(cmdw_args);
		return (127);
	}
	if (execve(path, cmdw_args, cmd->envar->mod) == -1)
	{
		perror("");
		return (1);
	}
	return (0);
}

int	executing_with_path(t_command *cmd, char **cmdw_args)
{
	struct stat	sb;

	if (stat(cmd->command, &sb) == 0 && S_ISDIR(sb.st_mode))
	{

		write(1, "That's a directory\n", 20);
		free_arguments(cmdw_args);
		return (126);
	}
	if (execve(cmd->command, cmdw_args, cmd->envar->mod) == -1)
	{
		perror("");
		return (1);
	}
	return (0);
}

int executing(t_command *cmd)
{
	char		**cmdw_args;
	int			returned;

	cmdw_args = adding_command(cmd);
	returned = 0;
	if (cmdw_args == NULL)
	{
		perror("");
		return (1);
	}
	if (is_path(cmd->command) == 0)
	{
		returned = executing_with_path(cmd, cmdw_args);
		return (returned);
	}
	else if (is_path(cmd->command) != 0)
	{
		returned = executing_without_path(cmd, cmdw_args);
		return (returned);
	}
	return (returned);
}

