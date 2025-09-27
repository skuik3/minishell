/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/27 17:54:52 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

t_env	*adding_env(t_command *cmd, char **envp)
{
	t_env	*env;

	(void)cmd;
	env = malloc(sizeof(t_env));
	if (env == NULL)
		return (ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), NULL);
	saving_env(&env->start, envp);
	saving_env(&env->mod, envp);
	env->exit_status = 0;
	return (env);
}

void	process_command(char *promt, t_biggie *bigs)
{
	t_command	*cmd;

	if (g_signal == SIGINT)
	{
		bigs->env->exit_status = 130;
		g_signal = 0;
	}
	cmd = run_shell_line(promt, bigs->env, bigs);
	if (cmd == NULL)
	{
		bigs->env->exit_status = bigs->exit_status;
		free(promt);
		return ;
	}
	cmd->envar = bigs->env;
	bigs->cmd = cmd;
	bigs->cmd_head = cmd;
	bigs->exit_bef = command_execution(bigs);
	if (g_signal != SIGINT)
		bigs->env->exit_status = bigs->exit_bef;
	add_history(promt);
	clean_big(bigs);
	free(promt);
}

void	minishell_loop(t_biggie *bigs)
{
	char	*promt;

	while (1)
	{
		signal(SIGINT, handle_signal_main);
		signal(EOF, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		promt = readline("minishell> ");
		if (promt == NULL)
			break ;
		process_command(promt, bigs);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_biggie	*bigs;

	(void)argc;
	(void)argv;
	bigs = setting_big();
	bigs->env = adding_env(NULL, envp);
	minishell_loop(bigs);
	free_big(bigs);
	return (0);
}
