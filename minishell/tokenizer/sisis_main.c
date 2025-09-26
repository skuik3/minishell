/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sisis_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:42:31 by skuik             #+#    #+#             */
/*   Updated: 2025/09/26 07:06:44 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_list(char **arr, const char *label)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	printf("  %s: ", label);
	while (arr[i])
	{
		printf("[%s] ", arr[i]);
		i++;
	}
	printf("\n");
}

int	is_exit_input(const char *line, ssize_t n)
{
	if (n == -1)
		return (1);
	if (n == 2 && line[0] == '\x11')
		return (1);
	if (!ft_strncmp(line, "exit", 4))
		return (1);
	return (0);
}

t_command	*run_shell_line(char *line, env_t *env)
{
	t_token		*tokens;
	t_command	*cmd_list;

	cmd_list = NULL;
	tokens = tokenize(line, env);
	if (!tokens)
	{
		return (NULL);
	}
	if (!validate_syntax(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	if (!init_commands(&cmd_list, tokens, env))
	{
		free_tokens(tokens);
		return (NULL);
	}
	free_tokens(tokens);
	return (cmd_list);
}
