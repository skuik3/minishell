/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/22 10:51:04 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int copy_string(char **env, char *orig_env)
{
    int i;

    i = 0;
    while (orig_env[i] != '\0')
        i++;
    *env = malloc(sizeof(char) * (i + 1));
    if (*env == NULL)
        return (ft_putstr_fd(ERR_MALLOC, 2), 1);
    i = 0;
    while (orig_env[i] != '\0')
    {
        (*env)[i] = orig_env[i];
        i++;
    }
    (*env)[i] = '\0';
    return (0);
}

int saving_env(char ***env, char *envp[])
{
    int i;

    i = 0;
    while (envp[i] != NULL)
        i++;
    *env = malloc(sizeof(char *) * (i + 1));
    if (*env == NULL)
        return (ft_putstr_fd(ERR_MALLOC, 2), 1);
    i = 0;
    while (envp[i] != NULL)
    {
        copy_string(&(*env)[i], envp[i]);
        i++;
    }
    env[i] = NULL;
    return (0);
}

int what_builtin(t_command *cmd)
{
    if (ft_strcmp(cmd->command, "echo") == 0)
        run_echo(cmd->arguments);
    if (ft_strcmp(cmd->command, "pwd") == 0)
        run_pwd();
    if (ft_strcmp(cmd->command, "cd") == 0)
    {
        if (cmd->arguments[1] != NULL)
            return (write(STDERR_FILENO, "Error\n", 6), 1);
        run_cd(cmd->arguments[0], cmd->envar);
    }
    if (ft_strcmp(cmd->command, "env") == 0)
        run_env(cmd->envar->mod);
    if (ft_strcmp(cmd->command, "exit") == 0)
        run_exit();
    if (ft_strcmp(cmd->command, "export") == 0)
        run_export(cmd->envar, cmd->arguments);
    if (ft_strcmp(cmd->command, "unset") == 0)
        run_unset(cmd->envar, cmd->arguments);

    // if (ft_strcmp(arguments[0], "test") == 0) // for tests, OK
    //      redirecting_in(arguments[1]);
    //      appending(arguments[1]);
    //      executing(arguments[1], envp);
    //     redirecting_out(arguments[1]);
    return (0);
}

// int anezkas_main(int argc, char *argv[], char *envp[])
// {
//     char *promt;
//     env_t *env;
//     int i;

//     env = malloc(sizeof(env_t));
//     if (env == NULL)
//         return (ft_putstr_fd(ERR_MALLOC, 2), 1);
//     saving_env(&env->start, envp);
//     saving_env(&env->mod, envp);
//     while (1)
//     {
//         promt = readline("");
//         what_builtin(promt, env);
//         add_history(promt);
//     }
//     return (0);
// }
