/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:03:31 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/08/11 15:02:06 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int redirecting_in(t_redir *redirin)
{
    if (access(redirin->filename, F_OK) == -1)
        return(ft_putstr_fd(ERR_NOTFILE, STDOUT_FILENO), 1);
    return (0);   
}

char *get_line_heredoc(t_redir *last)
{
    char *line;
    char *returned;

    signal(SIGINT, SIG_DFL);
    while (1 && g_signal != 2)
    {
        write (STDOUT_FILENO, "> ", 3);
        line = get_next_line(STDIN_FILENO);
        if (ft_strcmp(line, ft_strjoin(last->filename, "\n")) == 0)
                break ;
        returned = ft_strjoin(line, "\n");
    }
    return (returned);
}

int redirecting_heredoc(t_redir *heredoc)
{
    char *promt;
    int pid;
    int status;

    pid = fork();
    if (pid < -1)
        return (ft_putstr_fd(ERR_FORK, STDERR_FILENO), 1);
    else if (pid == 0)
    {
        promt = get_line_heredoc(heredoc);
        exit(0);
    }
    waitpid(pid, &status, 0);
    // while (1 && g_signal != 2)
    // {
    //     write (STDOUT_FILENO, "> ", 3);
    //     promt = get_next_line(STDIN_FILENO);
    //     if (promt == NULL)
    //         return(ft_putstr_fd(ERR_READ, STDERR_FILENO), 1);
    //     if (ft_strcmp(promt, ft_strjoin(heredoc->filename, "\n")) == 0)
    //         break ;
    //     promt = ft_strjoin(promt, "\n");
    // }
    // free(promt);
    return (0);
}

int last_heredoc(t_redir *last)
{
    int pid;
    int pipe_hdc[2];
    char *promt;
    int status;

    g_signal = 0;
    signal(SIGINT, handle_signal_child);
    if (pipe(pipe_hdc) == -1)
        return(ft_putstr_fd(ERR_PIPE, STDERR_FILENO), 1);
    pid = fork();
    if (pid < -1)
        return (ft_putstr_fd(ERR_FORK, STDERR_FILENO), 1);
    else if (pid == 0)
    {
        close(pipe_hdc[0]);
        promt = get_line_heredoc(last);
        if (g_signal != 2 || promt == NULL)
            write(pipe_hdc[1], promt, ft_strlen(promt));
        close(pipe_hdc[1]);
        exit(0);
    }
    close(pipe_hdc[1]);
    waitpid(pid, &status, 0);
    if (g_signal == 2)
    {
        close(pipe_hdc[0]);
        return (1);
    }
    if (dup2(pipe_hdc[0], STDIN_FILENO) == -1)
        return (1);
    close(pipe_hdc[0]);
    return (0);
}

// int last_heredoc(t_redir *last)
// {
//     int pid;
//     int pipe_hdc[2];
//     char *promt;
//     int status;

//     if (pipe(pipe_hdc) == -1)
//         return(ft_putstr_fd(ERR_PIPE, STDERR_FILENO), 1);
//     pid = fork();
//     if (pid < -1)
//         return (ft_putstr_fd(ERR_FORK, STDERR_FILENO), 1);
//     else if (pid == 0)
//     {
//         g_signal = 0;
//         signal(SIGINT, handle_signal_child);
//         close(pipe_hdc[0]);
//         while (1)
//         {
//             write (STDOUT_FILENO, "> ", 3);
//             promt = get_next_line(STDIN_FILENO);
//             if (ft_strcmp(promt, ft_strjoin(last->filename, "\n")) == 0)
//                 break ;
//             promt = ft_strjoin(promt, "\n");
//             write(pipe_hdc[1], promt, ft_strlen(promt));
//             // free(promt);
            
//         }
//         close(pipe_hdc[1]);
//         exit(0);
//     }
//     close(pipe_hdc[1]);
//     waitpid(pid, &status, 0);
//     if (dup2(pipe_hdc[0], STDIN_FILENO) == -1)
//         return (1);
//     close(pipe_hdc[0]);
//     return (0);
// }

int last_redirect_in(t_redir *last)
{
    int fd;
    char *input;
    char *promt;
    int returned;

    if (last->type == REDIR_IN)
    {
        if (access(last->filename, F_OK) == -1)
            return(ft_putstr_fd(ERR_NOTFILE, STDOUT_FILENO), 1);
        fd = open(last->filename, O_RDWR | O_CREAT, SHELL_DEFAULT);
        if (dup2(fd, STDIN_FILENO) == -1)
            return(ft_putstr_fd(ERR_DUP, STDERR_FILENO), 1);
        close (fd);
    }
    else
        returned = last_heredoc(last);
    return (returned);
}

int redirect_in(t_command *cmd)
{
    int i;
    int returned;

    i = 0;
    returned = 0;
    while (cmd->redir_in[i + 1] != NULL)
    {
        if (cmd->redir_in[i]->type == REDIR_IN)
            returned = redirecting_in(cmd->redir_in[i]);
        else if (cmd->redir_in[i]->type == REDIR_HEREDOC)
            returned = redirecting_heredoc(cmd->redir_in[i]);
        i++;
    }
    returned = last_redirect_in(cmd->redir_in[i]);
    return (returned);
}

int heredoc_present(t_redir **redir)
{
    int i;

    i = 0;
    while (redir[i] != NULL)
    {
        if (redir[i]->type == REDIR_HEREDOC)
            return (1);
        i++;
    }
    return (0);
}
