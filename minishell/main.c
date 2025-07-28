/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/28 13:22:33 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

env_t *adding_env(t_command *cmd, char **envp)
{
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
