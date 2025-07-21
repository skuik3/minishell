/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:28:08 by skuik             #+#    #+#             */
/*   Updated: 2025/07/21 14:02:58 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

const char *token_type_to_string(t_token_type type){
    switch (type) {
        case T_WORD:       return "WORD";
        case T_PIPE:       return "PIPE";
        case T_REDIR_IN:   return "REDIR_IN";
        case T_REDIR_OUT:  return "REDIR_OUT";
        case T_APPEND:     return "APPEND";
        case T_HEREDOC:    return "HEREDOC";
        case T_END:        return "END";
        case T_OR:         return "OR";
        case T_AND:        return "AND";
        case T_BG:         return "BG";
        default:           return "UNKNOWN";
    }
}

t_token *argv_to_token_list(int argc, char **argv)
{
    t_token *head = NULL;
    int i;

    i = 1;
    while (i < argc)
    {
        size_t len = strlen(argv[i]);
        t_token_type tp = get_token_type_len(argv[i], len);
        t_token *n = new_token(argv[i], len, tp);
        append_token(&head, n);
        i++;
    }
    return (head);
}
