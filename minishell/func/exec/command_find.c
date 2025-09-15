/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/15 12:01:08 by anezka           ###   ########.fr       */
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
        returned = run_cd(bigs->cmd->arguments, bigs->cmd->envar);
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
        return (130);
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
            signal(SIGINT, SIG_DFL);
            bigs->exit_status = executing(bigs->cmd);
            exit(bigs->exit_status);
        }
        waitpid(pid, &bigs->exit_status, 0);
        bigs->exit_status = WEXITSTATUS(bigs->exit_status);
        if (bigs->exit_status == 2 || g_signal == SIGINT)
            bigs->exit_status = 130;
    }
    if (bigs->cmd->redir_in != NULL)
        close_herepipe(bigs->cmd);
    restore_fd(stdout_orig, stdin_orig);
    return (bigs->exit_status);
}
//maybe check after changing bigs
void close_herepipe(t_command *cmd) 
{
    int i = 0;
    while (cmd->redir_in[i + 1] != NULL)
        i++;
    if (cmd->redir_in[i]->type == REDIR_HEREDOC)
        close(cmd->redir_in[i]->pipe_forhdc[0]);    
}

//check the exiting and statuses
//if exit status != 0, should maybe not continue and update exit status
//find pattern
//kcnkscs | cat >> return 0 ..works
// cat | kjcnkdc >> return 127 (after ctrl+c, because cat working normally)
//          ..this does not work in minishell
int multiple_commands(t_biggie *bigs)
{
    int pid;
    int orig_stdout;
    int orig_stdin;

    orig_stdout = dup(STDOUT_FILENO);
    orig_stdin = dup(STDIN_FILENO);
    if (orig_stdout == -1 || orig_stdin == -1)
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
        return (130);
    while (bigs->cmd->next != NULL && g_signal != SIGINT)
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
            signal(SIGINT, SIG_DFL);
            if (bigs->cmd->is_first == 1)
            {
                bigs->exit_status = first_multiple(bigs);
                // printf("BBBB>%d", bigs->exit_status);
                if (bigs->exit_status != 0) // should i just return exit status wihtout check, would make more sense
                    exit (bigs->exit_status);
            }
            else
                bigs->exit_status = other_multiple(bigs);
            exit(bigs->exit_status);
        }
        if (bigs->cmd->is_first == 1)
            close(bigs->pipe_cmd->pipe[1]);
        else
        {
            close(bigs->pipe_cmd->pipe[0]);
            close(bigs->pipe_cmd->next->pipe[1]);
            bigs->pipe_cmd = bigs->pipe_cmd->next;
        }
        if (bigs->cmd->redir_in != NULL)
            close_herepipe(bigs->cmd);
        bigs->cmd = bigs->cmd->next;
        // if (heredoc_present(cmd->redir_in) == 1) //uncomment here first
        
    }
    if (g_signal != SIGINT)
        bigs->exit_status = last_multiple(bigs);
    if (bigs->cmd->redir_in != NULL)
        close_herepipe(bigs->cmd);
    // while (wait(&status) > 1)
    //     ;
    return (bigs->exit_status);
}

int command_execution(t_biggie *bigs)
{
    t_command *head;

    g_signal = 0;
    bigs->cmd->is_first = 1;
    if (bigs->cmd->next == NULL)
    {
        bigs->exit_status = single_command(bigs);
        return (bigs->exit_status);
    }
    bigs->pipe_cmd = prepare_pipes(bigs->cmd);
    head = bigs->cmd;
    while (bigs->cmd->next != NULL)
    {
        bigs->cmd = bigs->cmd->next;
        bigs->cmd->is_first = 0;
    }
    bigs->cmd = head;
    bigs->exit_status = multiple_commands(bigs);
    return(bigs->exit_status);
}