/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:53:15 by skuik             #+#    #+#             */
/*   Updated: 2025/09/19 18:35:24 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*process_variable_expansion(char *dollar_pos, char *before, env_t *env)
{
	char	*var_name;
	char	*var_value;
	char	*after;
	char	*result;
	int		var_len;
	int		is_special_var;

	var_len = get_var_name_len(dollar_pos + 1);
	if (var_len == 0)
		return (handle_empty_var(before));
	var_name = extract_var_name(dollar_pos + 1, var_len);
	var_value = get_env_var(env, var_name);
	is_special_var = 0;
	if (var_name && ft_strcmp(var_name, "?") == 0)
		is_special_var = 1;
	after = expand_variables(dollar_pos + 1 + var_len, env);
	result = build_expansion_result(before, var_value, after);
	cleanup_expansion_vars(var_name, after, var_value, is_special_var);
	return (result);
}

char	*expand_variables(const char *input, env_t *env)
{
	char	*dollar_pos;
	char	*before;

	if (!input || !env)
		return (handle_no_expansion(input));
	dollar_pos = ft_strchr(input, '$');
	if (!dollar_pos)
		return (ft_strdup(input));
	before = ft_substr(input, 0, dollar_pos - input);
	return (process_variable_expansion(dollar_pos, before, env));
}
