/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:53:24 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/25 14:23:25 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int number_exit(char *args)
{
    int nb;

    nb = ft_atoi((const char*)(args));
    if (nb > 255)
        nb = nb % 256;
    else if (nb < 0)
        nb = 256 + nb;
    return (nb);
}

int just_nb(char *nb)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (nb[i] != '\0')
    {
        if ((nb[i] > '9' || nb[i] < '0') && (nb[i] != '+' && nb[i] != '-'))
            return (1);
        else if (nb[i] == '+' || nb[i] == '-')
            count++;
        i++;
    }
    if (count > 1)
        return (1);
    return (0);
}

int run_exit(t_biggie *bigs)
{
    if (bigs->cmd->arguments == NULL){
       printf("EXIT>%d", bigs->exit_bef);// exit prev command
        exit(bigs->exit_status);
    }
    else
    {
        if (bigs->cmd->arguments[1] != NULL)
            bigs->exit_status = 1;
        else if (just_nb(bigs->cmd->arguments[0]) != 0)
            bigs->exit_status = 255;
        else
            bigs->exit_status = number_exit(bigs->cmd->arguments[0]);
    }
    printf("EXIT>%d", bigs->exit_status);
    exit (bigs->exit_status);
}
