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

//redirecting > works to the last file only
// int redirecting_in(t_command *cmd)
// {
//     int fd;
//     int buff_len;
//     int dest;

//     dest = 0;
//     while (cmd->redir_in[dest] != NULL)
//         dest++;
//     buff_len = ft_strlen(cmd->arguments[0]);
//     if (access(cmd->redir_in[dest - 1], F_OK) == 0)
//     {
//         if (unlink(cmd->redir_in[dest - 1]) == -1){
//             ft_putstr_fd(ERR_FILE, 2);
//             return (1);
//         }
//     }
//     fd = open(cmd->redir_in[dest - 1], O_RDWR | O_CREAT, SHELL_DEFAULT);
//     if (fd == -1)
//     {
//         ft_putstr_fd(ERR_FILE, 2);
//         return (1);
//     }
//     write(fd, cmd->arguments[0], buff_len); 
//     close(fd);
//     return (0);
// }

// int appending(t_command *cmd)
// {
//     int fd;
//     int buff_len;
//     int dest;

//     buff_len = ft_strlen(cmd->arguments[0]);
//     dest = 0;
//     while (cmd->append[dest] != NULL)
//         dest++;
//     if (access(cmd->append[dest - 1], F_OK) != 0)
//         fd = open(cmd->append[dest - 1], O_RDWR | O_CREAT, SHELL_DEFAULT);
//     fd = open(cmd->append[dest - 1], O_RDWR | O_APPEND, SHELL_DEFAULT);
//     if (fd == -1)
//     {
//         ft_putstr_fd(ERR_FILE, 2);
//         return (1);
//     }
//     // printf("%d", fd);
//     write(fd, "\n", 1);
//     write (fd, cmd->arguments[0], buff_len);
//     write(fd, "\n", 1);
//     close(fd);
//     return (0);
// }