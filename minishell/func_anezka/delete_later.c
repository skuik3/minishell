// unset prev version

// int run_unset2(env_t *envp, char **arguments)
// {
//     int i;
//     int unset;
//     int   envp_len;
//     char *variable;

//     i = 0;
//     unset = -1;
//     if (arguments == NULL)
//         return (ft_putstr_fd(ERR_ARG, 2), 1);
//     variable = find_variable(arguments);
//     envp_len = counting_envlen(envp->mod);
//     while(envp->mod[i] != NULL)
//     {
//         if (envp->mod[i][0] == variable[0])
//         {
//             if (unset_variable(envp->mod[i], variable, i) != -2)
//                 unset = unset_variable(envp->mod[i], variable, i);
//         }
//         i++;
//     }
//     if (unset == -1)
//         return (0);
//     envp->mod = put_unset(envp->mod, unset);
//     get_order(envp->mod);
//     run_env(envp->mod);
//     return (0);
// }