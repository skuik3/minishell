/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/01 10:59:24 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int what_builtin(t_command *cmd)
{
    int returned;

    returned = 0;
    if (ft_strcmp(cmd->command, "echo") == 0)
        returned = run_echo(cmd->arguments);
    else if (ft_strcmp(cmd->command, "pwd") == 0)
        returned = run_pwd();
    else if (ft_strcmp(cmd->command, "cd") == 0)
        returned = run_cd(cmd->arguments[0], cmd->envar);
    else if (ft_strcmp(cmd->command, "env") == 0)
        returned = run_env(cmd->envar->mod);
    else if (ft_strcmp(cmd->command, "exit") == 0)
        returned = run_exit();
    else if (ft_strcmp(cmd->command, "export") == 0)
        returned = run_export(cmd->envar, cmd->arguments);
    else if (ft_strcmp(cmd->command, "unset") == 0)
        returned = run_unset(cmd->envar, cmd->arguments);
    else if (cmd->command != NULL)
        returned = executing(cmd);
    return (returned);
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

int restore_fd(int stdout_orig, int stdin_orig)
{
    if (dup2(stdout_orig, STDOUT_FILENO) == -1 
        || dup2(stdin_orig, STDIN_FILENO) == -1)
        return (ft_putstr_fd(ERR_DUP, STDERR_FILENO), 1);
    close(stdout_orig);
    close(stdin_orig);
    return (0);
}

int single_command(t_command *cmd)
{
    int pid;
    int status;
    int stdout_orig;
    int stdin_orig;

    stdout_orig = dup(STDOUT_FILENO);
    stdin_orig = dup(STDIN_FILENO);
    if (stdout_orig == -1 || stdin_orig == -1)
        return (ft_putstr_fd(ERR_DUP, STDERR_FILENO), 1);
    if (check_heredoc(cmd) == 1)
        return(restore_fd(stdout_orig, stdin_orig), 1);
    if (cmd->redir_in != NULL || cmd->redir_out != NULL)
    {
        if (check_redirect(cmd) == 1)
            return(restore_fd(stdout_orig, stdin_orig), 1);
    }
    if (is_builtint(cmd->command) == 0)
        status = what_builtin(cmd);
    else
    {
        pid = fork();
        if (pid < -1)
            return (ft_putstr_fd(ERR_FORK, STDERR_FILENO), 1);
        else if (pid == 0)
        {
            status = executing(cmd);
            exit(0);
        }
        waitpid(pid, &status, 0);
    }
    restore_fd(stdout_orig, stdin_orig);
    return (status);
}

int multiple_commands(t_command *cmd, t_pipe *pipe_cmd)
{
    int pid;
    int orig_stdout;
    int orig_stdin;
    int status;

    orig_stdout = dup(STDOUT_FILENO);
    orig_stdin = dup(STDIN_FILENO);
    if (orig_stdout == -1 || orig_stdin == -1)
        return (ft_putstr_fd(ERR_DUP, STDERR_FILENO), 1);
    if (check_heredoc(cmd) == 1)
        return(restore_fd(orig_stdout, orig_stdin), 1);
    while (cmd->next != NULL)
    {
        pid = fork();
        if (pid < -1)
            return (ft_putstr_fd(ERR_FORK, STDERR_FILENO), 1);
        else if (pid == 0)
        {
            if (cmd->is_first == 1){
                status = first_multiple(cmd, pipe_cmd);
                if (status == 1)
                    return (exit(1), 1);
            }
            else
                status = other_multiple(cmd, pipe_cmd);
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
        // if (heredoc_present(cmd->redir_in) == 1) //uncomment here first
        wait(&status);
    }
    status = last_multiple(cmd, pipe_cmd);
    return (status);
}

int command_execution(t_command *cmd)
{
    t_pipe *pipe_cmd;
    t_command *head;
    int status;

    pipe_cmd = prepare_pipes(cmd);
    if (cmd->next == NULL)
    {
        cmd->is_first = 1;
        status = single_command(cmd);
        return (status);
    }
    cmd->is_first = 1;
    head = cmd;
    while (cmd->next != NULL)
    {
        cmd = cmd->next;
        cmd->is_first = 0;
    }
    cmd = head;
        // status = multiple_commands(cmd, pipe_cmd);
    return(status);
}
