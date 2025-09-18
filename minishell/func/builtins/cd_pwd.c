/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:53:24 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/17 17:40:53 by skuik            ###   ########.fr       */
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
    if (path == NULL || ft_strcmp(path[0], "~") == 0) //check if ok
        path[0] = find_path(env, "HOME");
    if (path == NULL)
        return (1);
    if (chdir(path[0]) != 0)
    {
        perror("");
        return (1);
    }
    //just for easy check
    // run_pwd();
    free(path);
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
//CHANGE TO FT_ATOI
int number_exit(char *args)
{
    int nb;

    nb = atoi((const char*)(args));
    if (nb > 255)
        nb = nb % 256;
    else if (nb < 0)
        nb = 256 + nb;
    return (nb);
}

int run_exit(t_biggie *bigs)
{
    if (bigs->cmd->arguments == NULL){
        printf("EXIT>%d", bigs->exit_bef); // exit prev command
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