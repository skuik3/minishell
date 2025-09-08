/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:53:24 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/08 16:00:41 by anezkahavra      ###   ########.fr       */
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
                return (ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), NULL);
            ft_strlcpy(dest_var, &env->mod[i][len + 1], ft_strlen(env->mod[i]) - len);
        }
        i++;
    }
    return (dest_var);
}

int run_cd(char *path, env_t *env)
{
    if (path == NULL || path[0] == '~')
        path = find_path(env, "HOME");
    if (chdir(path) != 0)
    {
        perror("");
        return (1);
    }
    //just for easy check
    // run_pwd();
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

    i = 0;
    while (nb[i] != '\0')
    {
        if (nb[i] > '9' || nb[i] < '0')
            return (1);
        i++;
    }
    return (0);
}
// command not found >>127 not working
// ctrl+c >> 130 working in heredoc, not in child
// cislo >> cislo working
// cokoliv jineho >> 255
int run_exit(t_biggie *bigs)
{
    if (bigs->cmd->arguments[0] == NULL){
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
            bigs->exit_status = atoi((const char*)(bigs->cmd->arguments[0]));
    }
    printf("EXIT>%d", bigs->exit_status);
    exit (bigs->exit_status);
}