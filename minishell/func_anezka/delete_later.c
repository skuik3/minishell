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

// int anezkas_main(int argc, char *argv[], char *envp[])
// {
//     char *promt;
//     env_t *env;
//     int i;

//     env = malloc(sizeof(env_t));
//     if (env == NULL)
//         return (ft_putstr_fd(ERR_MALLOC, 2), 1);
//     saving_env(&env->start, envp);
//     saving_env(&env->mod, envp);
//     while (1)
//     {
//         promt = readline("");
//         what_builtin(promt, env);
//         add_history(promt);
//     }
//     return (0);
// }

// char *get_line_heredoc(t_redir *last)
// {
//     char *line;
//     char *returned;

//     signal(SIGINT, SIG_DFL);
//     while (1 && g_signal != 2)
//     {
//         write (STDOUT_FILENO, "> ", 3);
//         line = get_next_line(STDIN_FILENO);
//         if (ft_strcmp(line, ft_strjoin(last->filename, "\n")) == 0)
//                 break ;
//         returned = ft_strjoin(line, "\n");
//     }
//     return (returned);
// }

// int redirecting_heredoc(t_redir *heredoc)
// {
//     char *promt;
//     int pid;
//     int status;

//     pid = fork();
//     if (pid < -1)
//         return (ft_putstr_fd(ERR_FORK, STDERR_FILENO), 1);
//     else if (pid == 0)
//     {
//         promt = get_line_heredoc(heredoc);
//         exit(0);
//     }
//     waitpid(pid, &status, 0);
//     // while (1 && g_signal != 2)
//     // {
//     //     write (STDOUT_FILENO, "> ", 3);
//     //     promt = get_next_line(STDIN_FILENO);
//     //     if (promt == NULL)
//     //         return(ft_putstr_fd(ERR_READ, STDERR_FILENO), 1);
//     //     if (ft_strcmp(promt, ft_strjoin(heredoc->filename, "\n")) == 0)
//     //         break ;
//     //     promt = ft_strjoin(promt, "\n");
//     // }
//     // free(promt);
//     return (0);
// }

// int last_heredoc(t_redir *last)
// {
//     int pid;
//     int pipe_hdc[2];
//     char *promt;
//     int status;

//     g_signal = 0;
//     signal(SIGINT, handle_signal_child);
//     if (pipe(pipe_hdc) == -1)
//         return(ft_putstr_fd(ERR_PIPE, STDERR_FILENO), 1);
//     pid = fork();
//     if (pid < -1)
//         return (ft_putstr_fd(ERR_FORK, STDERR_FILENO), 1);
//     else if (pid == 0)
//     {
//         close(pipe_hdc[0]);
//         promt = get_line_heredoc(last);
//         if (g_signal != 2 || promt == NULL)
//             write(pipe_hdc[1], promt, ft_strlen(promt));
//         close(pipe_hdc[1]);
//         exit(0);
//     }
//     close(pipe_hdc[1]);
//     waitpid(pid, &status, 0);
//     if (g_signal == 2)
//     {
//         close(pipe_hdc[0]);
//         return (1);
//     }
//     if (dup2(pipe_hdc[0], STDIN_FILENO) == -1)
//         return (1);
//     close(pipe_hdc[0]);
//     return (0);
// }

// int last_heredoc(t_redir *last)
// {
//     int pid;
//     int pipe_hdc[2];
//     char *promt;
//     int status;

//     if (pipe(pipe_hdc) == -1)
//         return(ft_putstr_fd(ERR_PIPE, STDERR_FILENO), 1);
//     pid = fork();
//     if (pid < -1)
//         return (ft_putstr_fd(ERR_FORK, STDERR_FILENO), 1);
//     else if (pid == 0)
//     {
//         g_signal = 0;
//         signal(SIGINT, handle_signal_child);
//         close(pipe_hdc[0]);
//         while (1)
//         {
//             write (STDOUT_FILENO, "> ", 3);
//             promt = get_next_line(STDIN_FILENO);
//             if (ft_strcmp(promt, ft_strjoin(last->filename, "\n")) == 0)
//                 break ;
//             promt = ft_strjoin(promt, "\n");
//             write(pipe_hdc[1], promt, ft_strlen(promt));
//             // free(promt);
            
//         }
//         close(pipe_hdc[1]);
//         exit(0);
//     }
//     close(pipe_hdc[1]);
//     waitpid(pid, &status, 0);
//     if (dup2(pipe_hdc[0], STDIN_FILENO) == -1)
//         return (1);
//     close(pipe_hdc[0]);
//     return (0);
// }


// char *find_variable(char *arguments)
// {
//     char *variable;
//     int i;
//     int len;

//     len = 0;
//     while (arguments[len] != '\0' && arguments[len] != '=')
//         len++;
//     variable = malloc(sizeof(char) * (len + 1));
//     if (variable == NULL)
//     {
//         perror("");
//         return (NULL);
//     }
//     i = 0;
//     while (arguments[i] != '\0' && arguments[i] != '=')
//     {
//         variable[i] = arguments[i];
//         i++;
//     }
//     variable[i] = '\0';
//     return(variable);
// }

// int unset_variable(char *envp, char *variable, int i)
// {
//     int j;
//     int len;

//     j = 0;
//     len = ft_strlen(variable);
//     while (envp[j] != '\0' && variable[j] != '\0')
//     {
//         if (envp[j] != variable[j])
//             break ;
//         j++;
//     }
//     if (envp[j] == '=' && j == len && variable[j] == '\0')
//         return (i);
//     return (-2);
// }

// char **put_unset(char **old_env, int unset)
// {
//     int i;
//     int len;
//     char **new_envp;

//     i = 0;
//     len = counting_envlen(old_env);
//     new_envp = malloc(sizeof(char *) * (len + 1));
//     if (new_envp == NULL)
//     {
//         perror("");
//         return (NULL);
//     }
//     while (i < unset)
//     {
//        new_envp[i] = old_env[i];
//        i++; 
//     }
//     while (old_env[i + 1] != NULL)
//     {
//         new_envp[i] = old_env[i + 1];
//         i++; 
//     }
//     new_envp[i] = NULL;
//     // run_env(new_envp);
//     free(old_env);
//     return (new_envp);
// }

// int *find_unset(int *unset, char **arguments, env_t *envp)
// {
//     int i;
//     int j;
//     char *variable;

//     j = 0;
//     while (arguments[j] != NULL)
//     {
//         variable = find_variable(arguments[j]);
//         if (ft_strcmp(variable, arguments[j]) != 0)
//             return (free(variable), NULL);
//         i = 0;
//         unset[j] = -1;
//         while (envp->mod[i] != NULL)
//         {
//             if (envp->mod[i][0] == variable[0])
//             {
//                 if (unset_variable(envp->mod[i], arguments[j], i) != -2)
//                 {
//                     unset[j] = unset_variable(envp->mod[i], variable, i);
//                     return (unset);
//                 }
        
//             }
//             i++;
//         }
//         j++;
//     }
//     free(variable);
//     unset[j] = '\0';
//     return (unset);
// }

// int run_unset_cont(env_t *envp, char **arguments)
// {
//     int i;
//     int j;
//     int arglen;
//     int envplen;
//     int *unset;

//     i = 0;
//     j = 0;
//     if (arguments[0] == NULL)
//         return (ft_putstr_fd(ERR_ARG, STDERR_FILENO), 1);
//     // arglen = counting_envlen(arguments);
//     envplen = counting_envlen(envp->mod);
//     unset = malloc(sizeof(int) * (arglen * envplen + 1));
//     if (unset == NULL)
//     {
//         perror("");
//         return (1);
//     }
//     unset = find_unset(unset, arguments, envp);
//     if (unset == NULL) //check, dont delete
//         return (0);
//     while (unset[i] != '\0')
//     {
//         if (unset[i] != -1)
//             envp->mod = put_unset(envp->mod, unset[i]);
//         i++;
//     }
//     //for check
//     get_order(envp->mod);
//     run_env(envp->mod);
//     return (0);
// }

// int run_unset(env_t *envp, char **arguments)
// {
//     int i;
//     int returned;

//     i = 0;
//     returned = 0;
//     while (*arguments)
//     {
//         returned = run_unset_cont(envp, arguments);
//         arguments++;
//     }
//     return (returned);
// }
