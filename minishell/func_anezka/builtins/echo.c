/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:53:24 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/16 21:28:11 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int run_echo(char **string)
{
    int i;
    int k;

    i = 2;
    if (string[2] == NULL)
    {
        write(STDOUT_FILENO, "\n", 1);
        return (0);
    }
    if (ft_strcmp(string[2], "-n") == 0)
        i++;
    while (string[i] != NULL)
    {
        k = 0;
        while (string[i][k] != '\0')
        {
            write(STDOUT_FILENO, &string[i][k], 1);
            k++;
        }
        if (string[i + 1] != NULL)
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (ft_strcmp(string[2], "-n") != 0) //adding flag
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}