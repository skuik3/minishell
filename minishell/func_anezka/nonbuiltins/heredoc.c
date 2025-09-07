/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:03:31 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/07 18:09:09 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int last_heredoc(t_redir *last)
{
    int pid;

    char *promt;
    int status;

    last->pipe_forhdc = malloc(sizeof(int) * 2);
    if (last->pipe_forhdc == NULL)
    {
        perror("");
        return (1);
    }   
    if (pipe(last->pipe_forhdc) == -1)
    {
        perror("");
        return (1);
    }
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
        close(last->pipe_forhdc[0]);
        promt = get_line_heredoc(last);
        write(last->pipe_forhdc[1], promt, ft_strlen(promt));
        close(last->pipe_forhdc[1]);
        exit(0);
    }
    close(last->pipe_forhdc[1]);
    waitpid(pid, &status, 0);
    if (g_signal == SIGINT)
    {
        close(last->pipe_forhdc[0]);
        return (SIGINT);
    }
    // if (dup2(last->pipe_forhdc[0], STDIN_FILENO) == -1)
    // {
    //     perror("");
    //     return (1);
    // }
    close(last->pipe_forhdc[0]);
    // printf("statusheredoc>%d", status);
    return (0);
}

char *get_line_heredoc(t_redir *last)
{
    char *line;
    char *returned;

    returned = NULL;
    while (1 && g_signal != SIGINT)
    {
        write (STDOUT_FILENO, "> ", 3);
        line = get_next_line(STDIN_FILENO);
        if (ft_strcmp(line, ft_strjoin(last->filename, "\n")) == 0)
            break ;
        returned = ft_strjoin(returned, line);        
    }
    return (returned);
}

int redirecting_heredoc(t_redir *heredoc)
{
    char *promt;
    int pid;
    int status;

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
        promt = get_line_heredoc(heredoc);
        exit(0);
    }
    if (g_signal == SIGINT)
        return (SIGINT);
    waitpid(pid, &status, 0);
    return (status);
}

int do_heredoc(t_command *cmd)
{
    int i;
    int returned;
    // int hdc;

    i = 0;
    returned = 0;
    // hdc = where_last_heredoc(cmd, REDIR_HEREDOC);
    while (cmd->redir_in[i + 1] != NULL)
    {
        // printf("\nBBBB\n");
        if (cmd->redir_in[i]->type == REDIR_HEREDOC)
            returned = redirecting_heredoc(cmd->redir_in[i]);
        if (returned == SIGINT)
            return(returned);
        i++;
    }
    while (cmd->redir_in[i] != NULL)
    {
        // printf("\nCCCC\n");
        if (cmd->redir_in[i]->type == REDIR_HEREDOC)
            returned = last_heredoc(cmd->redir_in[i]);
        i++;
    }
    // printf("\nDDDD>%d\n", returned); 
    return (returned);
}

int heredoc_present(t_redir **redir)
{
    int i;

    i = 0;
    if (redir == NULL)
        return (0);
    while (redir[i] != NULL)
    {
        if (redir[i]->type == REDIR_HEREDOC)
            return (1);
        i++;
    }
    return (0);
}

int check_heredoc(t_command *cmd)
{
    int returned;

    returned = 0;
    // exit(0);
    if (cmd->next == NULL && cmd->is_first == 1)
    {
        // printf("\nAAAA\n");
        if (heredoc_present(cmd->redir_in) == 1)
            returned = do_heredoc(cmd);
        return (returned);
    }
    while (cmd != NULL)
    {
        // write(1, "B\n", 2);
        // printf("%s\n", cmd->command);

        if (heredoc_present(cmd->redir_in) == 1)
            returned = do_heredoc_multiple(cmd);
        if (returned == SIGINT)
            return(returned);
        cmd = cmd->next;
    }
    return (returned);
}