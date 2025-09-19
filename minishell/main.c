/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/19 16:07:01 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = 0;
int g_last_exit_status = 0;

env_t *adding_env(t_command *cmd, char **envp)
{
    env_t *env;

    (void)cmd; // unused parameter
    env = malloc(sizeof(env_t));
    if (env == NULL)
        return (ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), NULL);
    saving_env(&env->start, envp);
    saving_env(&env->mod, envp);
    return (env);
}


int main(int argc, char *argv[], char *envp[])
{
    char *promt;
    t_command *cmd;
    t_biggie *bigs;

    (void)argc;
    (void)argv;    
    bigs = setting_big();
    bigs->env = adding_env(NULL, envp);
    while (1)
    {
        signal(SIGINT, handle_signal_main);
        signal(EOF, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        promt = readline("minishell> ");
        if (promt == NULL)
            break;
        cmd = run_shell_line(promt, bigs->env);
        if (cmd == NULL)
        {
            free(promt);
            continue ;
        }
        cmd->envar = bigs->env;
        g_signal = 0;
        bigs->cmd = cmd;
        bigs->exit_bef = command_execution(bigs);
        g_last_exit_status = bigs->exit_bef;//new
        add_history(promt);
        clean_big(bigs);
        free(promt);
    }
    free_big(bigs);
    return (0);
}
