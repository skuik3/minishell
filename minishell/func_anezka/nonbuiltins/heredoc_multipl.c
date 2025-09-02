/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_multipl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:52:13 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/02 12:17:05 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// char *get_line_heredoc(t_redir *last)
// {
//     char *line;
//     char *returned;

//     returned = NULL;
//     while (1)
//     {
//         write (STDOUT_FILENO, "> ", 3);
//         line = get_next_line(STDIN_FILENO);
//         if (ft_strcmp(line, ft_strjoin(last->filename, "\n")) == 0)
//             break ;
//         returned = ft_strjoin(returned, line);        
//     }
//     return (returned);
// }

int last_heredoc_multiple(t_redir *last)
{
    int pid;
    char *promt;
    int status;

    last->pipe_forhdc = malloc(sizeof(int) * 2);
    if (last->pipe_forhdc == NULL)
        return(ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), 1);
    if (pipe(last->pipe_forhdc) == -1)
        return(ft_putstr_fd(ERR_PIPE, STDERR_FILENO), 1);
    pid = fork();
    if (pid < -1)
        return (ft_putstr_fd(ERR_FORK, STDERR_FILENO), 1);
    else if (pid == 0)
    {
        // dup2(last->pipe_forhdc[1], STDIN_FILENO);
        close(last->pipe_forhdc[0]);
        promt = get_line_heredoc(last);
        write(last->pipe_forhdc[1], promt, ft_strlen(promt));
        close(last->pipe_forhdc[1]);
        exit(0);
    }
    waitpid(pid, &status, 0);
    close(last->pipe_forhdc[1]);
    // if (dup2(last->pipe_forhdc[0], STDIN_FILENO) == -1)
    //     return (1);
    // close(last->pipe_forhdc[0]);
    return (0);
}

int do_heredoc_multiple(t_command *cmd)
{
    int i;
    int returned;
    // int hdc;

    i = 0;
    returned = 0;
    // hdc = where_last_heredoc(cmd, REDIR_HEREDOC);
    while (cmd->redir_in[i + 1] != NULL)
    {
        if (cmd->redir_in[i]->type == REDIR_HEREDOC)
            returned = redirecting_heredoc(cmd->redir_in[i]);
        i++;
    }
    // write(1, "C\n", 2);
    if (cmd->redir_in[i]->type == REDIR_HEREDOC)
       returned = last_heredoc_multiple(cmd->redir_in[i]);
    return (returned);
}

// int do_heredoc_multiple(t_command *cmd)
// {
//     int i;
//     int returned;
//     int hdc;

//     i = 0;
//     returned = 0;
//     hdc = where_last_heredoc(cmd, REDIR_HEREDOC);
//     while (i < hdc)
//     {
//         if (cmd->redir_in[i]->type == REDIR_HEREDOC)
//             returned = redirecting_heredoc(cmd->redir_in[i]);
//         i++;
//     }
//     while (cmd->redir_in[i] != NULL)
//     {
//         if (cmd->redir_in[i]->type == REDIR_HEREDOC)
//             returned = last_heredoc_multiple(cmd->redir_in[i]);
//         i++;
//     }
//     return (returned);
// }

