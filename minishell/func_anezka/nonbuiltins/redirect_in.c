/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:03:31 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/08/03 22:19:44 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int redirecting_in(t_redir *redirin)
{
    if (access(redirin->filename, F_OK) == -1)
        return(ft_putstr_fd(ERR_NOTFILE, STDOUT_FILENO), 1);
    return (0);   
}

int redirecting_heredoc(t_redir *herdoc)
{
    char *promt;

    while (1)
    {
        promt = readline(""); 
        if (ft_strcmp(promt, herdoc->filename) == 0)
            break ;
    }
    return (0);
}

int last_heredoc(t_redir *last)
{
    int pid;
    int *pipe_hdc;
    char *promt;
    int *status;

    if (pipe(pipe_hdc) == -1)
        return(ft_putstr_fd(ERR_PIPE, STDERR_FILENO), 1);
    pid = fork();
    if (pid < -1)
        return (ft_putstr_fd(ERR_FORK, STDERR_FILENO), 1);
    else if (pid == 0)
    {
        close(pipe_hdc[0]);
        while (1)
        {
            promt = readline("> ");
            if (ft_strcmp(promt, last->filename) == 0)
                break ;
            promt = ft_strjoin(promt, "\n");
            write(pipe_hdc[1], promt, ft_strlen(promt));
            
        }
        close(pipe_hdc[1]);
        exit(0);
    }
    if (dup2(pipe_hdc[0], STDIN_FILENO))
        return (0);
    close(pipe_hdc[0]);
    close(pipe_hdc[1]);
    waitpid(pid, &status, 0);
    return (0);
}

int last_redirect_in(t_redir *last)
{
    int fd;
    char *input;
    char *promt;

    if (last->type == REDIR_IN)
    {
        if (access(last->filename, F_OK) == -1) //issue here
            return(ft_putstr_fd(ERR_NOTFILE, STDOUT_FILENO), 1);
        fd = open(last->filename, O_RDWR | O_CREAT, SHELL_DEFAULT);
        if (dup2(fd, STDIN_FILENO) == -1)
            return(ft_putstr_fd(ERR_DUP, STDERR_FILENO), 1);
        close (fd);
    }
    else
        last_heredoc(last);
    return (0);
}

int redirect_in(t_command *cmd)
{
    int i;

    i = 0;
    while (cmd->redir_in[i + 1] != NULL)
    {
        if (cmd->redir_in[i]->type == REDIR_IN)
            redirecting_in(cmd->redir_in[i]);
        else if (cmd->redir_in[i]->type == REDIR_HEREDOC)
            redirecting_heredoc(cmd->redir_in[i]);
        i++;
    }
    last_redirect_in(cmd->redir_in[i]);
    return (0);
}
