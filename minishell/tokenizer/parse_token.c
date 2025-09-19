/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:59:57 by skuik             #+#    #+#             */
/*   Updated: 2025/09/19 18:22:45 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	handle_double_op(const char *input, size_t i, t_token **tokens)
{
	t_token_type	type;

	type = get_token_type_len(&input[i], 2);
	append_token(tokens, new_token(&input[i], 2, type));
	return (i + 2);
}

static	size_t	handle_single_op(const char *input, size_t i, t_token **tokens)
{
	t_token_type	type;

	type = get_token_type_len(&input[i], 1);
	append_token(tokens, new_token(&input[i], 1, type));
	return (i + 1);
}

size_t	parse_operator(const char *input, size_t i, t_token **tokens)
{
	if ((input[i] == '>' || input[i] == '<' || input[i] == '|'
			|| input[i] == '&')
		&& input[i + 1] == input[i])
		return (handle_double_op(input, i, tokens));
	return (handle_single_op(input, i, tokens));
}

size_t	parse_quoted(const char *input, size_t i, t_token **tokens)
{
	char	quote;
	size_t	start;

	quote = input[i++];
	start = i;
	while (input[i] && input[i] != quote)
		i++;
	append_token(tokens, new_token(&input[start], i - start, T_WORD));
	if (input[i] == quote)
		return (i + 1);
	return (i);
}

size_t	parse_word(const char *input, size_t i, t_token **tokens)
{
	size_t	start;

	start = i;
	while (input[i] && !isspace((unsigned char)input[i])
		&& !is_operator_start(input[i]))
		i++;
	append_token(tokens, new_token(&input[start], i - start, T_WORD));
	return (i);
}
