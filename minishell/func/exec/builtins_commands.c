/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:23:05 by anezka            #+#    #+#             */
/*   Updated: 2025/09/25 18:44:19 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	what_builtin(t_biggie *bigs)
{
	int	returned;

	returned = 0;
	if (ft_strcmp(bigs->cmd->command, "echo") == 0)
		returned = run_echo(bigs->cmd->arguments);
	else if (ft_strcmp(bigs->cmd->command, "pwd") == 0)
		returned = run_pwd();
	else if (ft_strcmp(bigs->cmd->command, "cd") == 0)
		returned = run_cd(bigs->cmd->arguments, bigs->cmd->envar);
	else if (ft_strcmp(bigs->cmd->command, "env") == 0)
		returned = run_env(bigs);
	else if (ft_strcmp(bigs->cmd->command, "exit") == 0)
		returned = run_exit(bigs);
	else if (ft_strcmp(bigs->cmd->command, "export") == 0)
		returned = run_export(bigs);
	else if (ft_strcmp(bigs->cmd->command, "unset") == 0)
		returned = run_unset(bigs->cmd->envar, bigs->cmd->arguments);
	else if (bigs->cmd->command != NULL)
		returned = executing(bigs->cmd);
	return (returned);
}

int	is_builtint(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (0);
	else if (ft_strcmp(command, "env") == 0)
		return (0);
	else if (ft_strcmp(command, "export") == 0)
		return (0);
	else if (ft_strcmp(command, "unset") == 0)
		return (0);
	else if (ft_strcmp(command, "exit") == 0)
		return (0);
	else if (ft_strcmp(command, "cd") == 0)
		return (0);
	else if (ft_strcmp(command, "pwd") == 0)
		return (0);
	return (1);
}
