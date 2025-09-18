/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:53:24 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/16 14:54:05 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int write_echo(char *argument)
{
    int i;

    i = 0;
    while (argument[i]!= '\0')
    {
        write(STDOUT_FILENO, &argument[i], 1);
        i++;
    }
    return (0);
}

int run_echo(char **arguments)
{
    int i;

    i = 0;
    if (arguments == NULL)
    {
        ft_putstr_fd("\n", STDOUT_FILENO);
        return (0);
    }
    if (ft_strcmp(arguments[0], "-n") == 0)
        i++;
    while (arguments[i] != NULL)
    {
        write_echo(arguments[i]);
        if (arguments[i + 1] != NULL)
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (ft_strcmp(arguments[0], "-n") != 0)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}
