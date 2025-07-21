/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:17:09 by skuik             #+#    #+#             */
/*   Updated: 2025/07/21 17:02:29 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool is_builtin(const char *cmd)
{
    return (
        !strcmp(cmd, "echo")   ||
        !strcmp(cmd, "cd")     ||
        !strcmp(cmd, "pwd")    ||
        !strcmp(cmd, "export") ||
        !strcmp(cmd, "unset")  ||
        !strcmp(cmd, "env")    ||
        !strcmp(cmd, "exit")
    );
}

// void execute_builtin(char **argv, char **envp)
// {
//     if (!argv || !argv[0])
//         return;
//     if (!strcmp(argv[0], "echo"))
//         run_echo(argv);
//     else if (!strcmp(argv[0], "cd"))
//         run_cd(argv[1]);
//     else if (!strcmp(argv[0], "pwd"))
//         run_pwd();
//     else if (!strcmp(argv[0], "export"))
//         run_export(envp, argv[1]);
//     else if (!strcmp(argv[0], "unset"))
//         run_unset(argv[1]);
//     else if (!strcmp(argv[0], "env"))
//         run_env(envp);
//     else if (!strcmp(argv[0], "exit"))
//         run_exit();
// }


void execute_external(t_token *tokens, char **envp)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        char **argv = tokens_to_argv(tokens);
        if (!argv || !argv[0])
        {
            fprintf(stderr, "Empty command\n");
            exit(1);
        }

        execve((argv[0]), argv, envp);
        perror("execve failed");
        free_argv(argv);
        exit(127);
    }
    else if (pid > 0)
    {
        int status;
        waitpid(pid, &status, 0);
    }
    else
        perror("fork failed");
}


// void execute_external(t_token *tokens)
// {
//     pid_t pid = fork();
//     if (pid == 0)
//     {
//         char **argv = tokens_to_argv(tokens);
//         execvp(argv[0], argv);
//         perror("exec failed");
//         free_argv(argv);
//         exit(1);
//     }
//     else if (pid > 0)
//     {
//         int status;
//         waitpid(pid, &status, 0);
//     }
//     else
//     {
//         perror("fork failed");
//     }
// }