/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:53:15 by skuik             #+#    #+#             */
/*   Updated: 2025/09/24 14:04:34 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_var_expansion_data(char *dollar_pos, char **var_name,
		int *var_len, int *is_special_var)
{
	char	*var_value;

	var_value = NULL;
	*var_len = get_var_name_len(dollar_pos + 1);
	if (*var_len == 0)
		return (NULL);
	*var_name = extract_var_name(dollar_pos + 1, *var_len);
	*is_special_var = 0;
	if (*var_name && ft_strcmp(*var_name, "?") == 0)
		*is_special_var = 1;
	return (var_value);
}

char	*process_var_expansion(char *dollar_pos, char *before, env_t *env)
{
	char	*var_name;
	char	*var_value;
	char	*after;
	char	*result;
	int		var_len;
	int		is_special_var;

	get_var_expansion_data(dollar_pos, &var_name, &var_len, &is_special_var);
	if (var_len == 0)
		return (handle_empty_var(before));
	var_value = get_env_var(env, var_name);
	after = expand_var(dollar_pos + 1 + var_len, env);
	result = build_expansion_result(before, var_value, after);
	cleanup_expansion_vars(var_name, after, var_value, is_special_var);
	return (result);
}

char	*expand_var(const char *input, env_t *env)
{
	char	*dollar_pos;
	char	*before;

	if (!input || !env)
		return (handle_no_expansion(input));
	dollar_pos = ft_strchr(input, '$');
	if (!dollar_pos)
		return (ft_strdup(input));
	before = ft_substr(input, 0, dollar_pos - input);
	return (process_var_expansion(dollar_pos, before, env));
}
