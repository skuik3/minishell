/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/08 09:55:22 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int what_builtin(char *argv, char *envp[])
{
    char **arguments;

    arguments = ft_split(argv,' ');
    if (ft_strcmp(arguments[0], "echo") == 0)
        run_echo(arguments);
    if (ft_strcmp(arguments[0], "pwd") == 0)
        run_pwd();
    if (ft_strcmp(arguments[0], "cd") == 0)
        run_cd(arguments[1]);
    if (ft_strcmp(arguments[0], "env") == 0)
        run_env(envp);
    if (ft_strcmp(arguments[0], "exit") == 0)
        run_exit();
    if (ft_strcmp(arguments[0], "export") == 0)
        run_export(envp, arguments[1]);
    //TODO UNSET
    // if (ft_strcmp(arguments[0], "unset") == 0)
    //     run_unset();
    //
    // if (ft_strcmp(arguments[0], "test") == 0) // for tests
    //     simple_redirecting(arguments[1]);
    if (ft_strcmp(arguments[0], "test") == 0)
        redirecting_add(arguments[1]);

    return (0);
}

int main(int argc, char *argv[], char *envp[]) // need to save envp somewhere for later use
{
    char *promt;

    while (1)
    {
        promt = readline("");
        what_builtin(promt, envp);
        add_history(promt);
    }
    return (0);
}