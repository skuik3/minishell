/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:08 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/16 19:13:46 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int run_env(char **envp)
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
//now added as a string, without recognizing variable and value, pr. JANA / should be JANA=''
int run_export(env_t *envp, char *arguments)
{
    int   i;

    i = 0;
    if (arguments == NULL)
    {
        get_order(envp->mod);
        run_env(envp->mod);
        return (0);
    }
    envp->mod = put_envp(envp->mod, arguments);
 // just fo easy check, delete later >> export with args is not printed
    get_order(envp->mod);
    run_env(envp->mod);
    return (0);
}

int run_unset(env_t *envp, char *arguments)
{
    int i;
    int j;
    int unset;
    int   envp_len;
    char **new_envp;
    char *variable;

    i = 0;
    j = 0;
    //proably not needed, arguments accecpt only name of the variable
    variable = find_variable(arguments);
    envp_len = counting_envlen(envp->mod);
    while(envp->mod[i] != NULL)
    {
        if (envp->mod[i][j] == variable[j])
        {
            if (unset_variable(envp->mod[i], variable, i) != -2)
                unset = unset_variable(envp->mod[i], variable, i);
        }
        i++;
    }
    printf("variable: %s, poradi: %d", variable, unset);
    // put_unset(envp->mod, new_envp->mod, unset);
    // get_order(new_envp->mod);
    // run_env(new_envp->mod);
    return (0);
}

