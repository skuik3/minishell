/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:49:21 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/18 20:25:38 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void handle_signal_main(int signal)
{

    if (signal == SIGINT) //ctrl+c
    {
        g_signal = SIGINT;
        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (signal == EOF) //ctrl+d managed in main by checking promt
        g_signal = EOF;
    // else if (signal == SIGQUIT) //ctrl+
    // managed in main by ignoring

}

void handle_signal_child(int signal)
{
    if (signal == SIGINT) //ctrl+c
    {
        g_signal = SIGINT;
        write(STDOUT_FILENO, "\n", 1);
    }
    else if (signal == EOF) //ctrl+d
        g_signal = EOF;
}

void handle_signal_heredoc(int signal)
{
    if (signal == SIGINT)
    {
        g_signal = SIGINT;
        ioctl(0, TIOCSTI, "\n");
        rl_redisplay();
    }
}

