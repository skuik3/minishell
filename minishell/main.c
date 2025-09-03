/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/01 23:49:31 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
    char *promt;
    t_command *cmd;

    if (!(cmd = malloc(sizeof(t_command))))
    {
        // ft_putstr_fd(ERR_MALLOC, 2);
        return (1);
    }
    while (1)
    {
        promt = readline("");
        t_command *cmds = run_shell_line(promt);
        free_cmd(cmds);
        add_history(promt);
    }
    return (0);
}
