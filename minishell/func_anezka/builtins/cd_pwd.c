/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:53:24 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/21 19:08:10 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *find_home(env_t *env)
{
    int i;
    char *variable;
    char *home;

    i = 0;
    while (env->mod[i] != NULL)
    {
        variable = find_variable(env->mod[i]);
        if (ft_strcmp(variable, "HOME") == 0)
        {
            home = malloc(sizeof(char) * (ft_strlen(env->mod[i] + 2)));
            if (home == NULL)
                return (ft_putstr_fd(ERR_MALLOC, 2), NULL);
            ft_strlcpy(home, &env->mod[i][5], ft_strlen(env->mod[i - 4]));
        }
        i++;
    }
    return (home);
}

int run_cd(char *path, env_t *env)
{
    if (path == NULL || path[0] == '~')
        path = find_home(env);
    if (chdir(path) != 0)
    {
        write(STDERR_FILENO, "Error\n", 6);
        return (1);
    }
    //just for easy check
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