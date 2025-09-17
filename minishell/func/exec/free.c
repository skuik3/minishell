/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:04:01 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/17 14:59:05 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void free_arguments(char **arguments) 
{
    int i;

    i = 0;
    if (arguments == NULL)
        return ;
    while (arguments[i] != NULL)
    {
        free(arguments[i]);
        arguments[i] = NULL;
        i++;
    }
    free(arguments);
    arguments = NULL;
}

void free_redir(t_redir **redir) {
    int i;

    i = 0;
    while (redir[i] != NULL)
    {
        free(redir[i]->filename);
        if (redir[i]->pipe_forhdc != NULL)
            free(redir[i]->pipe_forhdc);
        free(redir[i]);
        i++;
    }
    free(redir);
}

void free_env(env_t *env)
{
    int i;

    i = 0;
    while (env->start[i] != NULL)
    {
        free(env->start[i]);
        i++;
    }
    free(env->start);
    i = 0;
    while (env->mod[i] != NULL)
    {
        free(env->mod[i]);
        i++;
    }
    free(env->mod);
    free(env);
}

void free_commands(t_command *cmd)
{
    free(cmd->command);
    cmd->command = NULL;
    if (cmd->arguments != NULL)
        free_arguments(cmd->arguments);
    cmd->arguments = NULL;
    if (cmd->redir_in != NULL)
        free_redir(cmd->redir_in);
    cmd->redir_in = NULL;
    if (cmd->redir_out != NULL)
        free_redir(cmd->redir_out);
    cmd->redir_out = NULL;
    // if (cmd->envar != NULL)
    //     free_env(cmd->envar);
    // cmd->envar = NULL;
}

void free_pipes(t_pipe *pipe)
{
    free(pipe->pipe);
    pipe->pipe = NULL;
}

void free_big(t_biggie *bigs)
{
    t_command *current;
    
    if (bigs == NULL)
        return;
    while (bigs->cmd != NULL)
    {
        current = bigs->cmd;
        bigs->cmd = bigs->cmd->next;
        free_commands(current);
        free(current);

    }
    bigs->cmd = NULL;
    if (bigs->env != NULL)
        free_env(bigs->env);
    bigs->env = NULL;
    while (bigs->pipe_cmd != NULL)
    {
        free_pipes(bigs->pipe_cmd);
        bigs->pipe_cmd = bigs->pipe_cmd->next;
    }
    bigs->pipe_cmd = NULL;
    free(bigs);
    bigs = NULL;
}