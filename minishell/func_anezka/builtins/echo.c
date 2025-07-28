/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:53:24 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/28 23:01:39 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int run_echo(char **arguments)
{
    int i;
    int k;

    i = 0;
    if (arguments[0] == NULL)
    {
        ft_putstr_fd("\n", STDOUT_FILENO);
        return (0);
    }
    if (ft_strcmp(arguments[0], "-n") == 0)
        i++;
    while (arguments[i] != NULL)
    {
        k = 0;
        while (arguments[i][k] != '\0')
        {
            write(STDOUT_FILENO, &arguments[i][k], 1);
            k++;
        }
        if (arguments[i + 1] != NULL)
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (ft_strcmp(arguments[0], "-n") != 0)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}