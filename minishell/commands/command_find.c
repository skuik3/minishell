/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/08 16:50:05 by anezkahavra      ###   ########.fr       */
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
    //TODO UNSET, REDIRECTING_OUT
    // if (ft_strcmp(arguments[0], "unset") == 0)
    //     run_unset(); //same issue as export
    //     redirecting_out(arguments[1]);

    // if (ft_strcmp(arguments[0], "test") == 0) // for tests
    //      redirecting_in(arguments[1]);
    //      appending(arguments[1]);

    if (ft_strcmp(arguments[0], "test") == 0)
        executing(arguments[1], envp);
    
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