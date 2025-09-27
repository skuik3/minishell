/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:42:30 by skuik             #+#    #+#             */
/*   Updated: 2025/09/27 18:47:01 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	process_single_token(t_parse_params *params)
{
	size_t	new_i;

	if (is_operator_start(params->input[params->i]))
		return (parse_operator(params->input, params->i, params->tokens));
	params->result = NULL;
	new_i = parse_word_w_env(params);
	if (new_i == (size_t) - 1)
		return ((size_t) - 1);
	return (new_i);
}

static t_token	*tokenize_loop(const char *input, t_env *env, t_biggie *bigs)
{
	t_token			*tokens;
	size_t			i;
	size_t			new_i;
	t_parse_params	params;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		i = skip_spaces(input, i);
		if (!input[i])
			break ;
		params = (t_parse_params){input, i, &tokens, NULL, env, bigs};
		new_i = process_single_token(&params);
		if (new_i == (size_t) - 1)
		{
			free_tokens(tokens);
			return (NULL);
		}
		i = new_i;
	}
	return (tokens);
}

t_token	*tokenize(const char *input, t_env *env, t_biggie *bigs)
{
	return (tokenize_loop(input, env, bigs));
}
