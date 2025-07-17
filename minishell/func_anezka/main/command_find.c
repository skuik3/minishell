/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/16 23:03:42 by anezkahavra      ###   ########.fr       */
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

int what_builtin(char *argv, env_t *env)
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
        run_env(env->mod);
    if (ft_strcmp(arguments[0], "exit") == 0)
        run_exit();
    if (ft_strcmp(arguments[0], "export") == 0)
        run_export(env, arguments[1]);
    if (ft_strcmp(arguments[0], "unset") == 0)
        run_unset(env, arguments[1]);

    // if (ft_strcmp(arguments[0], "test") == 0) // for tests, OK
    //      redirecting_in(arguments[1]);
    //      appending(arguments[1]);
    //      executing(arguments[1], envp);
    //     redirecting_out(arguments[1]);
    return (0);
}

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
        what_builtin(promt, env);
        add_history(promt);
    }
    return (0);
}
