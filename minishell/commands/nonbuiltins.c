/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nonbuiltins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:27:14 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/08 17:03:03 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// needed commands recognition
// very very basic functionality
// maybe check with acces if file exist >> possible error
int executing(char *str, char *evnp[])
{       
     //now defined, later when tokenization works, should be generally usable
    char *const argv[] = {"ls", "-l", NULL}; //depends on tokenization from readline, do later
    
    execve("/bin/ls", argv, evnp); 
    return (0);
}
//finishes process
//probably neeed to use fork()
