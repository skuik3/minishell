/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:59:57 by skuik             #+#    #+#             */
/*   Updated: 2025/09/19 18:22:53 by skuik            ###   ########.fr       */
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
