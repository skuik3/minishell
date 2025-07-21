/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/21 18:36:04 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
    char *promt;
    env_t *env;
    t_command *cmd;

    cmd->envar = malloc(sizeof(env_t));
    if (cmd->envar == NULL)
        return (ft_putstr_fd(ERR_MALLOC, 2), 1);
    saving_env(&cmd->envar->start, envp);
    saving_env(&cmd->envar->mod, envp);
    while (1)
    {
        promt = readline("");
        cmd = run_shell_line(promt);
        what_builtin(cmd, env);
        add_history(promt);
    }
    return (0);
}
