/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:08 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/09 15:36:04 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int run_env(char *envp[])
{
    int i;

    i = 0;
    while (envp[i] != NULL)
    {
        printf("%s\n", envp[i]);
        i++;
    }
    return (0);
}
// now takes is as a string, without recognizing what is variable, value
// export behaves diff > order by abc, env not and missing some variables?
int run_export(char *envp[], char *arguments)
{
    char **new_envp;
    int   envp_len;
    int   len;
    int   i;

    if (arguments == NULL)
    {
        run_env(envp);
        return (0);
    }
    envp_len = counting_envlen(envp) + 2;
    new_envp = malloc(sizeof(char *) * envp_len); 
    i = 0;
    get_order(envp);
    while (envp[i] != NULL)
    {
        put_envp(envp[i], new_envp, i);
        i++;
    }
    put_envp(arguments, new_envp, i);
    new_envp[i + 1] = NULL;
    run_env(new_envp);
    return (0);
}

// int run_unset(char *envp[], char *arguments)
// {

// }

// OLD VERSION WITH ABC ORDER
//
// order by abc, might not be needed
// int run_export(char *envp[], char *arguments)
// {
//     int i;
//     int start;

//     i = 0;
//     if (arguments == NULL)
//         run_env(envp);
//     else
//     {
//         start = find_start(envp, arguments); 
//         while (i <= start)
//         {
//             printf("%s\n", envp[i]);
//             i++;
//         }
//         printf("%s\n", arguments);
//         while (envp[i] != NULL)
//         {
//             printf("%s\n", envp[i]);
//             i++;
//         }
//     }
//     return (0);
// }