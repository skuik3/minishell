/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/21 17:21:26 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
    char *promt;
    env_t *env;
    int i;

    env = malloc(sizeof(env_t));
    if (env == NULL)
        return (ft_putstr_fd(ERR_MALLOC, 2), 1);
    saving_env(&env->start, envp);
    saving_env(&env->mod, envp);
    while (1)
    {
        promt = readline("");
        run_shell_line(promt);
        add_history(promt);
    }
    return (0);
}