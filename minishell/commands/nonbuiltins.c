/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nonbuiltins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:27:14 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/09 11:38:23 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// needed commands recognition
// very very basic functionality

// maybe check with acces if file exist >> possible error
// maybe check status if child process works correctly
int executing(char *str, char *evnp[])
{       
     //now defined, later when tokenization works, should be generally usable
    char *const argv[] = {"ls", "-l", NULL}; //depends on tokenization from readline, do later
    int pid;
    int status;

    pid = fork();
    if (pid < -1)
    {
        write(STDERR_FILENO, "Error forking\n", 15);
        return (1);
    }
    else if (pid == 0)
        execve("/bin/ls", argv, evnp); 
    else if (pid > 0)
        waitpid(pid, &status, 0); // if not use for check, status not needed >> NULL
    return (0);
}

