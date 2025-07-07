/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   park_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:20:02 by skuik             #+#    #+#             */
/*   Updated: 2025/07/06 19:26:07 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token *argv_to_token_list(int argc, char **argv)
{
    t_token *head = NULL;
    int i;
    
    i = 1;
    while (i < argc)
    {
        t_token_type type = get_token_type(argv[i]);
        append_token(&head, new_token(argv[i], strlen(argv[i]), type));
        i++;
    }
    return head;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "You should: %s [command args...]\n", argv[0]);
        return 1;
    }
    printf("Args given: %d\n", argc - 1);
    t_token *tokens = argv_to_token_list(argc, argv);
    print_tokens(tokens);
    free_tokens(tokens);
    return 0;
}
