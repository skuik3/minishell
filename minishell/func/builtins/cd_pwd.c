/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezka <anezka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:53:24 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/17 08:56:39 by anezka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *find_path(env_t *env, char *find_var)
{
    int i;
    int len;
    char *variable;
    char *dest_var;

    i = 0;
    len = ft_strlen(find_var);
    while (env->mod[i] != NULL)
    {
        variable = find_variable(env->mod[i]);
        if (ft_strcmp(variable, find_var) == 0)
        {
            dest_var = malloc(sizeof(char) * (ft_strlen(env->mod[i] + 2)));
            if (dest_var == NULL)
                return (free(variable),ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), NULL);
            ft_strlcpy(dest_var, &env->mod[i][len + 1], ft_strlen(env->mod[i]) - len);
        }
        i++;
        free(variable);
    }
    return (dest_var);
}

int run_cd(char **path, env_t *env)
{
    char *temp;

    if (path == NULL || ft_strcmp(path[0], "~") == 0) //check if ok
        temp = find_path(env, "HOME");
    if (temp == NULL)
        return (1);
    if (path != NULL || ft_strcmp(path[0], "~") != 0)
        temp = path[0];
    if (chdir(temp) != 0)
    {
        perror("");
        return (1);
    }
    free_arguments(path);
    free(temp);
    //just for easy check
    // run_pwd();path[0]
    // free(path);
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
