/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:02:45 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/14 15:39:55 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *find_variable(char *arguments)
{
    char *variable;
    int i;
    int len;

    len = 0;
    while (arguments[len] != '\0' || arguments[len] != '=')
        len++;
    variable = malloc(sizeof(char) * len + 1);
    if (variable == NULL)
        return (write (STDERR_FILENO, "Mallocing failed\n", 18), NULL);
    i = 0;
    while (arguments[i] != '\0'|| arguments[i] != '=')
    {
        variable[i] = arguments[i];
        i++;
    }
    variable[i] = '\0';
    return(variable);
}

int unset_variable(char *envp, char *variable, int i)
{
    int j;
    int len;

    j = 0;
    len = ft_strlen(variable);
    while (envp[j] != '\0' || variable[j] != '\0')
    {
        if (envp[j] != variable[j])
            break ;
        j++;
    }
    if (envp[j] == '=' && j == (len + 1))
        return (i);
    return (-2);
}

int put_unset(char *old_envp[], char *new_envp[], int unset)
{
   int i;

   i = 0;
   while (i < unset)
   {
        put_envp(old_envp[i], new_envp, i);
        i++;
   }
   while (old_envp[i + 1] != NULL)
   {
        put_envp(old_envp[i + 1], new_envp, i);
        i++;
   }
   new_envp[i] = NULL;
   return(0);
}