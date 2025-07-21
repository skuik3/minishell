/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:38:30 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/21 10:15:56 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct environment_variables
{
    char **start;
    char **mod;
} env_t;


//builtin fce
int what_builtin(char *argv, env_t *env);
int run_pwd(void);
int run_echo(char **string);
int run_cd(char *path, env_t *env); //todo home
int run_env(char **envp);
int run_exit(void); //todo s ciselkami
int run_export(env_t *env, char *arguments);
int run_unset(env_t *env, char *arguments); 

//utils
int saving_env(char ***env, char *envp[]);
int copy_string(char **env, char *orig_env);
int find_start(char *envp[], char *arguments);
int counting_envlen(char **envp);
char  **put_envp(char **old_envp, char *new_arg);
int get_order(char **envp);
char *find_variable(char *arguments);
char **put_unset(char **old_env, int unset);
int unset_variable(char *envp, char *variable, int i);
void	ft_putstr_fd(char *s, int fd);
char *find_envar(env_t *env, char *find);

int redirecting_in(char *str);
int redirecting_out(char *str);
int appending(char *str);

int executing(char *str, char *evnp[]);

//libft_later
int	ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
int	ft_numstrings(const char *s, int c);
unsigned int	findend(const char *s, int c, int i);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

//for readability
#define SHELL_DEFAULT 00644

#define ERR_MALLOC "Malloc failure\n"
#define ERR_ARG "Not enough arguments\n"

#endif