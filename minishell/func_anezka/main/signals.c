/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:49:21 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/04 12:12:40 by anezkahavra      ###   ########.fr       */
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
    // else if (signal == SIGQUIT) //ctrl+
    // {
    //     g_signal = SIGQUIT;
    //     kill(0, SIGINT);
    // }
    else if (signal == EOF) //ctrl+d, now segfaults
        g_signal = EOF;
}

void handle_signal_child(int signal)
{
    if (signal == SIGINT) //ctrl+c
    {
        g_signal = SIGINT;
        write(STDOUT_FILENO, "\n", 1);
    }
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

