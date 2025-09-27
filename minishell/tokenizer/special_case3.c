/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:53:15 by skuik             #+#    #+#             */
/*   Updated: 2025/09/27 14:05:32 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_var_data(char *dollar_pos, char **var_name, int *var_len,
	int *is_special_var)
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

char	*build_and_clean(char *before, t_exp_vars vars)
{
	char	*result;

	result = build_exp_result(before, vars.var_value, vars.after);
	cleanup_vars(vars.var_name, vars.after, vars.var_value,
		vars.is_special_var);
	return (result);
}

static char	*process_empty_var(char *before, char *dollar_pos, t_env *env)
{
	char	*after;
	char	*result;

	after = expand_var(dollar_pos + 1, env);
	result = join_exp_parts(before, "$", after);
	if (after)
		free(after);
	return (result);
}

char	*process_var(char *dollar_pos, char *before, t_env *env)
{
	char		*var_name;
	int			var_len;
	int			is_special_var;
	t_exp_vars	vars;

	get_var_data(dollar_pos, &var_name, &var_len, &is_special_var);
	if (var_len == 0)
		return (process_empty_var(before, dollar_pos, env));
	vars.var_name = var_name;
	vars.var_value = get_env_var(env, var_name);
	vars.after = expand_var(dollar_pos + 1 + var_len, env);
	vars.is_special_var = is_special_var;
	return (build_and_clean(before, vars));
}

char	*expand_var(const char *input, t_env *env)
{
	char	*dollar_pos;
	char	*before;

	if (!input || !env)
		return (handle_no_exp(input));
	dollar_pos = ft_strchr(input, '$');
	if (!dollar_pos)
		return (ft_strdup(input));
	before = ft_substr(input, 0, dollar_pos - input);
	return (process_var(dollar_pos, before, env));
}
