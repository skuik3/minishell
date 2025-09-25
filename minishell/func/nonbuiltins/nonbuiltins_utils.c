/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nonbuiltins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:05:16 by anezka            #+#    #+#             */
/*   Updated: 2025/09/25 15:19:25 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_path(char *command)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(command);
	while (command[i] != '\0')
	{
		if (command[i] == '/')
			break ;
		i++;
	}
	if (i == len)
		return (1);
	return (0);
}

char *command_path(t_command *cmd)
{
	char	*env_path;
	char	**arr_path;
	int		i;
	char	*path;

	i = 0;
	env_path = find_path(cmd->envar, "PATH");
	if (env_path == NULL)
		return (NULL);
	arr_path = ft_split(env_path, ':');
	while (arr_path[i] != NULL)
	{
		path = ft_strjoin(arr_path[i], "/");
		path = ft_strjoin(path, cmd->command);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free(env_path);
	free(arr_path);
	return (NULL);
}

char **adding_command(t_command *cmd)
{
	char	**cmdw_args;
	int		arr_len;
	int		i;

	arr_len = 0;
	if (cmd->arguments != NULL)
		arr_len = counting_envlen(cmd->arguments);
	cmdw_args = malloc(sizeof(char *) * (arr_len + 2));
	if (cmdw_args == NULL)
	{
		perror("");
		return (NULL);
	}
	cmdw_args[0] = ft_strdup(cmd->command);
	i = 1;
	while (cmd->arguments != NULL && cmd->arguments[i - 1] != NULL)
	{
		cmdw_args[i] = ft_strdup(cmd->arguments[i - 1]);
		i++;
	}
	cmdw_args[i] = NULL;
	return(cmdw_args);
}
