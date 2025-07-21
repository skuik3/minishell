/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tok_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:27:01 by skuik             #+#    #+#             */
/*   Updated: 2025/07/21 17:02:42 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void parse_token_loop(t_token *tok, t_cmd_builder *b)
{
    while (tok && tok->type != T_PIPE)
    {
        handle_token(tok, b);
        if ((tok->type >= T_REDIR_IN && tok->type <= T_HEREDOC) && tok->next)
            tok = tok->next;
        tok = tok->next;
    }
}

char **list_to_array(t_list *list)
{
    t_list *tmp = list;
    int count;
    int i;

    i = 0;
    count = 0;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    char **arr = malloc(sizeof(char *) * (count + 1));
    if (!arr)
        return (NULL);
    tmp = list;
    while (i < count)
    {
        arr[i] = strdup((char *)tmp->content);
        tmp = tmp->next;
        i++;
    }
    arr[count] = NULL;
    return (arr);
}

void parse_tokens(t_token *tok, t_command **out)
{
    t_cmd_builder b;
    b.cmd = malloc(sizeof(t_command));
    if (!b.cmd)
        return;
    memset(b.cmd, 0, sizeof(t_command));
    b.args = b.redir_in = b.redir_out = NULL;
    parse_token_loop(tok, &b);
    b.cmd->arguments = list_to_array(b.args);
    b.cmd->redir_in = list_to_array(b.redir_in);
    b.cmd->redir_out = list_to_array(b.redir_out);
    *out = b.cmd;
}
