/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:08 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/17 13:41:58 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//ISSUE IF AFTER INV ARGUMENT!!
int run_env(char **envp)
{
    int i;

    i = 0;
    if (envp == NULL)
    {
        perror("");
        return (1);
    }
    while (envp[i] != NULL)
    {
        ft_putstr_fd(envp[i], STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        i++;
    }
    return (0);
}
