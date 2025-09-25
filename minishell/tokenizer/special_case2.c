/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:53:15 by skuik             #+#    #+#             */
/*   Updated: 2025/09/24 17:11:00 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_exp_parts(char *before, char *expansion, char *after)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(before, expansion);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, after);
	return (result);
}

char	*handle_no_exp(const char *input)
{
	if (!input)
		return (strdup(""));
	return (strdup(input));
}

char	*handle_empty_var(char *before)
{
	char	*result;

	result = ft_strjoin(before, "$");
	return (result);
}

void	cleanup_vars(char *var_name, char *after, char *var_value,
	int is_special)
{
	if (var_name)
		free(var_name);
	if (after)
		free(after);
	if (is_special && var_value)
		free(var_value);
}

char	*build_exp_result(char *before, char *var_value, char *after)
{
	char	*result;

	if (var_value)
		result = join_exp_parts(before, var_value, after);
	else
		result = join_exp_parts(before, "", after);
	return (result);
}
