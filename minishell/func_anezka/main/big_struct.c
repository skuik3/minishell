/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:44:46 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/08 11:04:30 by anezkahavra      ###   ########.fr       */
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
    // new->final_bef = 0;
    // new->pipes = NULL;
    // new->type = NULL;
    return(new);
}
