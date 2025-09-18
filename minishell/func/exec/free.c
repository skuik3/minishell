/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:04:01 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/18 14:41:46 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void free_arguments(char **arguments) 
{
    int i;

    i = 0;
    while (arguments[i] != NULL)
    {
        free(arguments[i]);
        i++;
    }
    free(arguments);
}

void free_redir(t_redir **redir, int count)//int count is new too
{
    int i;
    //new
    if (!redir || count <= 0)
        return;
    //
    i = 0;
    //while (redir[i] != NULL)
    while (i < count)
    {
        //free(redir[i]->filename);
        //free(redir[i]->pipe_forhdc);
        //free(redir[i]);
        if (redir[i])//new
        {
            if (redir[i]->filename)
                free(redir[i]->filename);
            if (redir[i]->pipe_forhdc)
                free(redir[i]->pipe_forhdc);
            free(redir[i]);
        }
        i++;//
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
        free_redir(cmd->redir_in, cmd->redir_in_count);//free_redir(cmd->redir_in);//this was before 
    cmd->redir_in = NULL;
    if (cmd->redir_out != NULL)
        free_redir(cmd->redir_out, cmd->redir_out_count);//free_redir(cmd->redir_out);//this was before
    cmd->redir_out = NULL;
    // if (cmd->envar != NULL)
    //     free_env(cmd->envar);
    // cmd->envar = NULL;
}

void free_pipes(t_pipe *pipe)
{
    //free(pipe->pipe);
    //pipe->pipe = NULL;
    if (!pipe)
        return;
    if (pipe->pipe)
        free(pipe->pipe);
    free(pipe);
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
        free(current);//new
    }
    bigs->cmd = NULL;
    if (bigs->env != NULL)
        free_env(bigs->env);
    bigs->env = NULL;
    while (bigs->pipe_cmd != NULL)
    {
        //free_pipes(bigs->pipe_cmd);
        t_pipe *temp = bigs->pipe_cmd;//new
        bigs->pipe_cmd = bigs->pipe_cmd->next;
        free_pipes(temp);//new
    }
    bigs->pipe_cmd = NULL;
    free(bigs);
    bigs = NULL;
}