/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:44:46 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/17 15:00:51 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_biggie *setting_big(void)
{
    t_biggie *new;

    new = malloc(sizeof(t_biggie));
    if (new == NULL)
    {
        perror("");
        return (NULL);
    }
    new->cmd = NULL;
    new->env = NULL;
    new->exit_status = 0;
    new->pipe_cmd = NULL;
    // new->final_bef = 0;
    // new->pipes = NULL;
    // new->type = NULL;
    return(new);
}

void clean_big(t_biggie *bigs)
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
}
