/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/05 15:35:52 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int what_builtin(t_biggie *bigs)
{
    int returned;

    returned = 0;
    if (ft_strcmp(bigs->cmd->command, "echo") == 0)
        returned = run_echo(bigs->cmd->arguments);
    else if (ft_strcmp(bigs->cmd->command, "pwd") == 0)
        returned = run_pwd();
    else if (ft_strcmp(bigs->cmd->command, "cd") == 0)
        returned = run_cd(bigs->cmd->arguments[0], bigs->cmd->envar);
    else if (ft_strcmp(bigs->cmd->command, "env") == 0)
        returned = run_env(bigs->cmd->envar->mod);
    else if (ft_strcmp(bigs->cmd->command, "exit") == 0)
        returned = run_exit(bigs);
    else if (ft_strcmp(bigs->cmd->command, "export") == 0)
        returned = run_export(bigs->cmd->envar, bigs->cmd->arguments);
    else if (ft_strcmp(bigs->cmd->command, "unset") == 0)
        returned = run_unset(bigs->cmd->envar, bigs->cmd->arguments);
    else if (bigs->cmd->command != NULL)
        returned = executing(bigs->cmd);
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
        {
            perror("");
            return (1);
        }
    close(stdout_orig);
    close(stdin_orig);
    return (0);
}

int single_command(t_biggie *bigs)
{
    int pid;
    int stdout_orig;
    int stdin_orig;

    stdout_orig = dup(STDOUT_FILENO);
    stdin_orig = dup(STDIN_FILENO);
    if (stdout_orig == -1 || stdin_orig == -1)
    {
        perror("");
        return (1);
    }
    bigs->exit_status = check_heredoc(bigs->cmd);
    if (bigs->exit_status == 1)
    {
        perror("");
        return (1);
    }
    if (bigs->exit_status == SIGINT)
        return (2);
    if (bigs->cmd->redir_in != NULL || bigs->cmd->redir_out != NULL)
    {
        if (check_redirect(bigs->cmd) == 1)
        {
            perror("");
            return (1); 
        }
    }
    if (is_builtint(bigs->cmd->command) == 0)
        bigs->exit_status = what_builtin(bigs);
    else
    {
        signal(SIGINT, handle_signal_child);
        pid = fork();
        if (pid < -1)
        {
            perror("");
            return (1);
        }
        else if (pid == 0)
        {
            bigs->exit_status = executing(bigs->cmd);
            exit(bigs->exit_status);
        }
        waitpid(pid, &bigs->exit_status, 0);
    }
    restore_fd(stdout_orig, stdin_orig);
    return (bigs->exit_status);
}

void close_herepipe(t_command *cmd) {
    int i = 0;
    while (cmd->redir_in[i + 1] != NULL)
        i++;
    if (cmd->redir_in[i]->type == REDIR_HEREDOC)
        close(cmd->redir_in[i]->pipe_forhdc[0]);    
}

//check the exiting and statuses if not weird
int multiple_commands(t_command *cmd, t_pipe *pipe_cmd)
{
    int pid;
    int orig_stdout;
    int orig_stdin;
    int status;

    orig_stdout = dup(STDOUT_FILENO);
    orig_stdin = dup(STDIN_FILENO);
    if (orig_stdout == -1 || orig_stdin == -1)
    {
        perror("");
        return (1);
    }
    status = check_heredoc(cmd);
    if (status == 1)
    {
        perror("");
        return (1);
    }
    if (status == SIGINT)
        return (2);
    while (cmd->next != NULL && g_signal != SIGINT)
    {
        pid = fork();
        if (pid < -1)
        {
            perror("");
            return (1);
        }
        else if (pid == 0)
        {
            signal(SIGINT, SIG_DFL);
            if (cmd->is_first == 1)
            {
                status = first_multiple(cmd, pipe_cmd);
                if (status == 1)
                    exit (1);
            }
            else
                status = other_multiple(cmd, pipe_cmd);
            exit(status);
        }
        if (cmd->is_first == 1)
            close(pipe_cmd->pipe[1]);
        else
        {
            close(pipe_cmd->pipe[0]);
            close(pipe_cmd->next->pipe[1]);
            pipe_cmd = pipe_cmd->next;
        }
        if (cmd->redir_in != NULL)
            close_herepipe(cmd);
        cmd = cmd->next;
        // if (heredoc_present(cmd->redir_in) == 1) //uncomment here first
        
    }
    if (g_signal != SIGINT)
        status = last_multiple(cmd, pipe_cmd);
    // while (wait(&status) > 1)
    //     ;
    return (status);
}

int command_execution(t_biggie *bigs)
{
    t_pipe *pipe_cmd;
    t_command *head;
    int status;

    g_signal = 0;
    bigs->cmd->pipe_cmd = prepare_pipes(bigs->cmd);
    bigs->cmd->is_first = 1;
    if (bigs->cmd->next == NULL)
    {
        bigs->exit_status = single_command(bigs);
        return (status);
    }
    head = bigs->cmd;
    while (bigs->cmd->next != NULL)
    {
        bigs->cmd = bigs->cmd->next;
        bigs->cmd->is_first = 0;
    }
    bigs->cmd = head;
    bigs->exit_status = multiple_commands(bigs->cmd, pipe_cmd);
    return(status);
}
