/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrank <ahavrank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:49:21 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/25 18:37:28 by ahavrank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_signal_main(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == EOF)
		g_signal = EOF;
}

void	handle_signal_child(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (signal == EOF)
		g_signal = EOF;
}

void	handle_signal_heredoc(int signal)
{
	if (signal == SIGINT)
		g_signal = SIGINT;
}
