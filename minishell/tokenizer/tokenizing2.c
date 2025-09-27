/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:42:30 by skuik             #+#    #+#             */
/*   Updated: 2025/09/27 18:45:56 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	pr_quoted_part(t_parse_params *params)
{
	size_t		start;
	char		quote;
	t_exp_data	data;

	quote = params->input[params->i++];
	start = params->i;
	while (params->input[params->i] && params->input[params->i] != quote)
		params->i++;
	if (!params->input[params->i])
	{
		if (quote == '"')
			printf("unexpected EOF while looking for matching `\"'\n");
		else
			printf("unexpected EOF while looking for matching `''\n");
		printf("syntax error: unexpected end of file\n");
		if (params->bigs)
			params->bigs->exit_status = 2;
		return (-1);
	}
	data = (t_exp_data){params->input, start, params->i, (quote == '"')};
	append_seg_w_expans(params->result, data, params->env);
	if (params->input[params->i] == quote)
		params->i++;
	return (params->i);
}

size_t	pr_unquoted_part(const char *input, size_t i, char **result, t_env *env)
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

size_t	process_quoted_word(t_parse_params *params, char **result)
{
	size_t	new_i;

	params->result = result;
	new_i = pr_quoted_part(params);
	if (new_i == (size_t) - 1)
		return (-1);
	return (new_i);
}

size_t	parse_word_w_env(t_parse_params *params)
{
	char	*result;
	size_t	new_i;

	result = ft_strdup("");
	while (params->input[params->i] && !isspace(params->input[params->i])
		&& !is_operator_start(params->input[params->i]))
	{
		if (params->input[params->i] == '"' || params->input[params->i] == '\'')
		{
			new_i = process_quoted_word(params, &result);
			if (new_i == (size_t) - 1)
			{
				free(result);
				return (-1);
			}
			params->i = new_i;
		}
		else
			params->i = pr_unquoted_part(params->input, params->i, &result,
					params->env);
	}
	append_token(params->tokens, new_token(result, ft_strlen(result), T_WORD));
	free(result);
	return (params->i);
}
