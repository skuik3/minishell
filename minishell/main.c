/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/23 19:00:39 by skuik            ###   ########.fr       */
/*   Updated: 2025/07/28 13:22:33 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

env_t *adding_env(t_command *cmd, char **envp)

{
    char *promt;
    t_command *cmd;

    if (!(cmd = malloc(sizeof(t_command))))
    {
        ft_putstr_fd(ERR_MALLOC, 2);
        return (1);
    }
    if (!(cmd->envar = malloc(sizeof(env_t))))
    {
        free(cmd);
        ft_putstr_fd(ERR_MALLOC, 2);
        return (1);
    }
    saving_env(&cmd->envar->start, envp);
    saving_env(&cmd->envar->mod, envp);
    while (1)
    {
        promt = readline("");
        t_command *cmds = run_shell_line(promt);
        free_cmd(cmds);
        add_history(promt);
    }
    return (0);
    env_t *env;

    env = malloc(sizeof(env_t));
    if (env == NULL)
        return (ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), NULL);
    saving_env(&env->start, envp);
    saving_env(&env->mod, envp);
    return (env);
}


// int main(int argc, char *argv[], char *envp[])
// {
//     char *promt;
//     t_command *cmd;

//     while (1)
//     {
//         promt = readline("");
//         cmd = run_shell_line(promt);
//         cmd->envar = adding_env(cmd, envp);
//         what_builtin(cmd);
//         add_history(promt);
//     }
//     return (0);
// }
