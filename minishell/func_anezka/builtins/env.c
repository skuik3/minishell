/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:08 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/03 10:57:49 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
        printf("%s\n", envp[i]); //ft_printf
        i++;
    }
    return (0);
}
