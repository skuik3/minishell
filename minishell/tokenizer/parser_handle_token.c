/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:24:13 by skuik             #+#    #+#             */
/*   Updated: 2025/07/21 17:02:52 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list *ft_lstnew(void *content)
{
    t_list *node = malloc(sizeof(t_list));
    if (!node)
        return (NULL);
    node->content = content;
    node->next = NULL;
    return (node);
}

void ft_lstadd_back(t_list **lst, t_list *new_node)
{
    t_list *current = *lst;

    if (!lst || !new_node)
        return;
    if (!*lst)
    {
        *lst = new_node;
        return;
    }
    while (current->next)
        current = current->next;
    current->next = new_node;
}

void handle_token(t_token *tok, t_cmd_builder *b)
{
    if (tok->type == T_WORD)
    {
        if (!b->cmd->command)
            b->cmd->command = strdup(tok->value);
        ft_lstadd_back(&b->args, ft_lstnew(strdup(tok->value)));
    }
    handle_in_redir(tok, b);
    handle_out_redir(tok, b);
}

void handle_in_redir(t_token *tok, t_cmd_builder *b)
{
    if (tok->type == T_REDIR_IN && tok->next)
        ft_lstadd_back(&b->redir_in, ft_lstnew(strdup(tok->next->value)));
    if (tok->type == T_HEREDOC && tok->next)
        b->cmd->heredoc = strdup(tok->next->value);
}

void handle_out_redir(t_token *tok, t_cmd_builder *b)
{
    if (tok->type == T_REDIR_OUT && tok->next)
        ft_lstadd_back(&b->redir_out, ft_lstnew(strdup(tok->next->value)));
    if (tok->type == T_APPEND && tok->next)
        b->cmd->append = strdup(tok->next->value);
}
