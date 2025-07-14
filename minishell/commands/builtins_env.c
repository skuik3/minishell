/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:08 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/14 15:43:48 by anezkahavra      ###   ########.fr       */
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

// adds only first arg, after putting another deletes previous args > just be ok after creating a struct;
// now takes is as a string, without recognizing what is variable, value
int run_export(char *envp[], char *arguments)
{
    char **new_envp;
    int   envp_len;
    int   i;

    envp_len = counting_envlen(envp) + 2;
    new_envp = malloc(sizeof(char *) * envp_len); 
    if (new_envp == NULL)   
        return (write (STDERR_FILENO, "Mallocing failed\n", 18), 1);
    i = 0;
    if (arguments == NULL)
    {
        get_order(envp);
        run_env(envp);
        return (0);
    }
    while (envp[i] != NULL)
    {
        put_envp(envp[i], new_envp, i);
        i++;
    }
    put_envp(arguments, new_envp, i);
    new_envp[i + 1] = NULL;
    // just fo easy check, delete later >> export with args is not printed
    get_order(new_envp);
    run_env(new_envp);
    return (0);
}

// int run_unset(char *envp[], char *arguments)
// {
//     int i;
//     int j;
//     int unset;
//     int   envp_len;
//     char **new_envp;
//     char *variable;

//     i = 0;
//     j = 0;
//     variable = find_variable(arguments);
//     envp_len = counting_envlen(envp);
//     while(envp[i] != NULL)
//     {
//         if (envp[i][j] == variable[j])
//             unset = unset_variable(envp[i], variable, i);
//         i++;
//     }
//     put_unset(envp, new_envp, unset);
//     get_order(new_envp);
//     run_env(new_envp);
//     return (0);
// }
