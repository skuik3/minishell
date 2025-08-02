/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/08/02 17:45:28 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int what_builtin(t_command *cmd)
{
    if (ft_strcmp(cmd->command, "echo") == 0)
        run_echo(cmd->arguments);
    else if (ft_strcmp(cmd->command, "pwd") == 0)
        run_pwd();
    else if (ft_strcmp(cmd->command, "cd") == 0)
        run_cd(cmd->arguments[0], cmd->envar);
    else if (ft_strcmp(cmd->command, "env") == 0)
        run_env(cmd->envar->mod);
    else if (ft_strcmp(cmd->command, "exit") == 0)
        run_exit();
    else if (ft_strcmp(cmd->command, "export") == 0)
        run_export(cmd->envar, cmd->arguments);
    else if (ft_strcmp(cmd->command, "unset") == 0)
        run_unset(cmd->envar, cmd->arguments);
    else if (cmd->command != NULL)
        executing(cmd);
    return (0);
}


int is_builtint(char *command)
{
    if (ft_strcmp(command, "echo") == 0)
        return (0);
    else if (ft_strcmp(command, "env") == 0)
        return (0);
    else if (ft_strcmp(command, "export") == 0)
        return (0);
    else if (ft_strcmp(command, "unset") == 0)
        return (0);
    else if (ft_strcmp(command, "exit") == 0)
        return (0);
    else if (ft_strcmp(command, "cd") == 0)
        return (0);
    else if (ft_strcmp(command, "pwd") == 0)
        return (0);
    return (1);
}

int single_command(t_command *cmd)
{
    int pid;
    int status;

    if (is_builtint(cmd->command) == 0)
        what_builtin(cmd);
    else
    {
        pid = fork();
        if (pid < -1)
            return (ft_putstr_fd(ERR_FORK, STDERR_FILENO), 1);
        else if (pid == 0)
            executing(cmd);
        else if (pid > 0)
            waitpid(pid, &status, 0); // if not use for check, status not needed >> NULL
    }
    return (0);
}

int multiple_commands(t_command *cmd, t_pipe *pipe_cmd)
{
    int pid;
    int orig_stdout;
    int status;

    orig_stdout = dup(STDOUT_FILENO);
    if (orig_stdout == -1)
        return (ft_putstr_fd(ERR_DUP, STDERR_FILENO), 1);
    while (cmd->next != NULL) //last command not included
    {
        pid = fork();
        if (pid < -1)
            return (ft_putstr_fd(ERR_FORK, STDERR_FILENO), 1);
        else if (pid == 0)
        {
            if (cmd->is_first == 1)
                first_multiple(cmd, pipe_cmd);
            else
                other_multiple(cmd, pipe_cmd);
            exit(0);
        }
        if (cmd->is_first == 1)
            close(pipe_cmd->pipe[1]);
        else
        {
            close(pipe_cmd->pipe[0]);
            close(pipe_cmd->next->pipe[1]);
            pipe_cmd = pipe_cmd->next;
        }
        cmd = cmd->next;
    }
    last_multiple(cmd, pipe_cmd);
    return (0);
}

int command_execution(t_command *cmd)
{
    t_pipe *pipe_cmd;
    t_command *head;

    pipe_cmd = prepare_pipes(cmd);
    if (cmd->next == NULL)
    {
        single_command(cmd);
        return (0);
    }
    cmd->is_first = 1;
    head = cmd;
    while (cmd->next != NULL)
    {
        cmd = cmd->next;
        cmd->is_first = 0;
    }
    cmd = head;
        multiple_commands(cmd, pipe_cmd);
    return(0);
}
