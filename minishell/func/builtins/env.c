/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:08 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/18 19:49:41 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//ISSUE IF AFTER INV ARGUMENT!!
int run_env(t_biggie *bigs)
{
    int i;
    char **env;

    env = bigs->cmd->envar->mod;
    if (bigs->cmd->arguments != NULL)
        return (1);
    i = 0;
    if (env == NULL)
    {
        perror("");
        return (1);
    }
    while (env[i] != NULL)
    {
        ft_putstr_fd(env[i], STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        i++;
    }
    return (0);
}
