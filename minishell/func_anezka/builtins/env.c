/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:08 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/08/06 14:17:15 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int run_env(char **envp)
{
    int i;

    i = 0;
    if (envp == NULL)
    {
        ft_putstr_fd(ERR_BC, STDERR_FILENO);
        return (1);
    }
    while (envp[i] != NULL)
    {
        printf("%s\n", envp[i]); //ft_printf
        i++;
    }
    return (0);
}
