/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniing2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:42:30 by skuik             #+#    #+#             */
/*   Updated: 2025/09/24 14:14:35 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	pr_quoted_part(const char *input, size_t i, char **result, env_t *env)
{
	size_t		start;
	char		quote;
	t_exp_data	data;

	quote = input[i++];
	start = i;
	while (input[i] && input[i] != quote)
		i++;
	data = (t_exp_data){input, start, i, (quote == '"')};
	append_seg_w_expans(result, data, env);
	if (input[i] == quote)
		i++;
	return (i);
}

size_t	pr_unquoted_part(const char *input, size_t i, char **result, env_t *env)
{
	size_t		start;
	t_exp_data	data;

	start = i;
	while (input[i] && !isspace(input[i])
		&& !is_operator_start(input[i]) && input[i] != '"' && input[i] != '\'')
		i++;
	data = (t_exp_data){input, start, i, true};
	append_seg_w_expans(result, data, env);
	return (i);
}

size_t	parse_word_w_env(const char *input, size_t i, t_token **tokens,
	env_t *env)
{
	char	*result;

	result = ft_strdup("");
	while (input[i] && !isspace(input[i]) && !is_operator_start(input[i]))
	{
		if (input[i] == '"' || input[i] == '\'')
			i = pr_quoted_part(input, i, &result, env);
		else
			i = pr_unquoted_part(input, i, &result, env);
	}
	append_token(tokens, new_token(result, ft_strlen(result), T_WORD));
	free(result);
	return (i);
}

t_token	*tokenize(const char *input, env_t *env)
{
	t_token	*tokens;
	size_t	i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		i = skip_spaces(input, i);
		if (!input[i])
			break ;
		if (is_operator_start(input[i]))
			i = parse_operator(input, i, &tokens);
		else
			i = parse_word_w_env(input, i, &tokens, env);
	}
	return (tokens);
}
