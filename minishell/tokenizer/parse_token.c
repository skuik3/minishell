/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:59:57 by skuik             #+#    #+#             */
/*   Updated: 2025/09/11 21:54:43 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *new_token(const char *str, size_t len, t_token_type type, int pos)
{
	t_token *tok;

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

t_redir_type get_redir_type(const char *str, size_t len)
{
	if (strncmp(str, ">", len) == 0)
		return REDIR_OUT;
	if (strncmp(str, ">>", len) == 0)
		return REDIR_APPEND;
	if (strncmp(str, "<", len) == 0)
		return REDIR_IN;
	if (strncmp(str, "<<", len) == 0)
		return REDIR_HEREDOC;
	return (0);
}

t_token_type get_token_type_len(const char *str, size_t len)
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

static size_t handle_double_op(const char *input, size_t i, t_token **tokens)
{
	t_token_type type;

	type = get_token_type_len(&input[i], 2);
	append_token(tokens, new_token(&input[i], 2, type, i));
	return (i + 2);
}

static	size_t handle_single_op(const char *input, size_t i, t_token **tokens)
{
	t_token_type type;

	type = get_token_type_len(&input[i], 1);
	append_token(tokens, new_token(&input[i], 1, type, i));
	return (i + 1);
}

size_t	parse_operator(const char *input, size_t i, t_token **tokens)
{
	if ((input[i] == '>' || input[i] == '<' || input[i] == '|' || input[i] == '&')
		&& input[i + 1] == input[i])
		return (handle_double_op(input, i, tokens));
	return (handle_single_op(input, i, tokens));
}

size_t	parse_quoted(const char *input, size_t i, t_token **tokens)
{
	char quote;
	size_t start;

	quote = input[i++];
	start = i;
	while (input[i] && input[i] != quote)
		i++;
	append_token(tokens, new_token(&input[start], i - start, T_WORD, start));
	if (input[i] == quote)
		return (i + 1);
	return (i);
}

size_t	parse_word(const char *input, size_t i, t_token **tokens)
{
	size_t start;

	start = i;
	while (input[i] && !isspace((unsigned char)input[i]) && !is_operator_start(input[i]))
		i++;
	append_token(tokens, new_token(&input[start], i - start, T_WORD, start));
	return (i);
}
