/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:44:46 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/15 11:50:27 by skuik            ###   ########.fr       */
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
    t_command *next;

    if (bigs == NULL)
        return;
    current = bigs->cmd;
    while (current != NULL)
    {
        next = current->next;
        //free_commands(current);
        current = next;
    }
    bigs->cmd = NULL;
}