/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:24:13 by skuik             #+#    #+#             */
/*   Updated: 2025/09/03 11:18:21 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list *ft_lstnew(void *content)
{
    t_list *node;

    node = malloc(sizeof(t_list));
    if (!node)
        return (NULL);
    node->content = content;
    node->next = NULL;
    return (node);
}

void ft_lstadd_back(t_list **lst, t_list *new_node)
{
    t_list *current;

    if (!lst || !new_node)
        return;
    if (!*lst)
    {
        *lst = new_node;
        return;
    }
    current = *lst;
    while (current->next)
        current = current->next;
    current->next = new_node;
}

static t_redir *make_redir(t_token *tok)
{
    t_redir *r;

    if (!tok || !tok->next)
        return (NULL);
    r = malloc(sizeof(t_redir));
    if (!r)
        return (NULL);
    r->filename = strdup(tok->next->value);
    if (tok->type == T_REDIR_IN)
        r->type = REDIR_IN;
    else if (tok->type == T_REDIR_OUT)
        r->type = REDIR_OUT;
    else if (tok->type == T_REDIR_APPEND)
        r->type = R_APPEND;
    else if (tok->type == T_REDIR_HEREDOC)
        r->type = R_HEREDOC;
    return (r);
}

void handle_token(t_token *tok, t_cmd_builder *b)
{
    t_redir *redir;

    if (tok->type == T_WORD)
    {
        if (!b->cmd->cmd_str)
            b->cmd->cmd_str = strdup(tok->value);
        ft_lstadd_back(&b->args, ft_lstnew(strdup(tok->value)));
    }
    if (tok->type >= T_REDIR_IN && tok->type <= T_REDIR_HEREDOC)
    {
        redir = malloc(sizeof(t_redir));
        if (!redir)
            return;
        redir->filename = strdup(tok->next ? tok->next->value : "");
        if (tok->type == T_REDIR_IN)
            redir->type = REDIR_IN;
        else if (tok->type == T_REDIR_OUT)
            redir->type = REDIR_OUT;
        else if (tok->type == T_REDIR_APPEND)
            redir->type = R_APPEND;
        else if (tok->type == T_REDIR_HEREDOC)
            redir->type = R_HEREDOC;
        ft_lstadd_back(&b->redirs, ft_lstnew(redir));
        if (tok->type == T_REDIR_HEREDOC && tok->next)
            b->cmd->cmd_str = strdup(tok->next->value);
    }
}
