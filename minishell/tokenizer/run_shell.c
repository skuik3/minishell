/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:42:31 by skuik             #+#    #+#             */
/*   Updated: 2025/09/27 18:48:08 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*run_shell_line(char *line, t_env *env, t_biggie *bigs)
{
	t_token		*tokens;
	t_command	*cmd_list;

	cmd_list = NULL;
	tokens = tokenize(line, env, bigs);
	if (!tokens)
	{
		return (NULL);
	}
	if (!validate_syntax(tokens))
	{
		free_tokens(tokens);
		if (bigs)
			bigs->exit_status = 2;
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
