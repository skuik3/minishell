/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:53:24 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/16 22:50:45 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//now works, later have to add cd without arguments >> using environment variables to set it, when cc done with tokens and struct finished
int run_cd(char *path)
{
    // if (path == NULL)
    //     path = "/home"
    if (chdir(path) != 0)
    {
        write(STDERR_FILENO, "Error\n", 6);
        return (1);
    }
    run_pwd();
    return (0);
}

int run_pwd(void)
{
    char *wd;
    char buff[PATH_MAX + 1];
    int i;

    wd = getcwd(buff, PATH_MAX + 1);
    if (wd != NULL)
    {
        i = 0;
        while (wd[i] != '\0')
        {
            write(STDOUT_FILENO, &wd[i], 1);
            i++;
        }
        write(STDOUT_FILENO, "\n", 1);
    }
    return (0);
}

int run_exit(void)
{
    exit(0);
}