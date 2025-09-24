/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:59:57 by skuik             #+#    #+#             */
/*   Updated: 2025/09/24 17:23:43 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*new_token(const char *str, size_t len, t_token_type type)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = strndup(str, len);
	if (!tok->value)
	{
		free(tok);
		return (NULL);
	}
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

t_redir	*new_redir(t_token *tok, t_redir_type type)
{
	t_redir	*r;

	if (!tok)
		return (NULL);
	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->filename = strdup(tok->value);
	if (!r->filename)
	{
		free(r);
		return (NULL);
	}
	r->type = type;
	r->pipe_forhdc = NULL;
	r->position = 0;
	return (r);
}

t_redir_type	get_redir_type_from_token(t_token_type tok_type)
{
	if (tok_type == T_REDIR_IN)
		return (REDIR_IN);
	if (tok_type == T_REDIR_HEREDOC)
		return (REDIR_HEREDOC);
	if (tok_type == T_REDIR_OUT)
		return (REDIR_OUT);
	if (tok_type == T_REDIR_APPEND)
		return (REDIR_APPEND);
	return (REDIR_IN);
}

t_redir_type	get_redir_type(const char *str, size_t len)
{
	if (strncmp(str, ">", len) == 0)
		return (REDIR_OUT);
	if (strncmp(str, ">>", len) == 0)
		return (REDIR_APPEND);
	if (strncmp(str, "<", len) == 0)
		return (REDIR_IN);
	if (strncmp(str, "<<", len) == 0)
		return (REDIR_HEREDOC);
	return (0);
}

t_token_type	get_token_type_len(const char *str, size_t len)
{
	if (len == 2)
	{
		if (strncmp(str, "||", 2) == 0)
			return (T_OR);
		if (strncmp(str, "&&", 2) == 0)
			return (T_AND);
		if (strncmp(str, ">>", 2) == 0)
			return (T_REDIR_APPEND);
		if (strncmp(str, "<<", 2) == 0)
			return (T_REDIR_HEREDOC);
	}
	else if (len == 1)
	{
		if (*str == '|')
			return (T_PIPE);
		if (*str == '&')
			return (T_BG);
		if (*str == ';')
			return (T_END);
		if (*str == '>')
			return (T_REDIR_OUT);
		if (*str == '<')
			return (T_REDIR_IN);
	}
	return (T_WORD);
}
