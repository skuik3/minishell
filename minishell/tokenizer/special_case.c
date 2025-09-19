/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:53:15 by skuik             #+#    #+#             */
/*   Updated: 2025/09/19 18:26:49 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_var_char(char c, int is_first)
{
	if (is_first)
		return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

int	get_var_name_len(const char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	if (str[0] == '?')
		return (1);
	if (!is_valid_var_char(str[0], 1))
		return (0);
	while (str[len] && is_valid_var_char(str[len], 0))
		len++;
	return (len);
}

char	*extract_var_name(const char *str, int len)
{
	char	*var_name;
	int		i;

	i = 0;
	if (len <= 0)
		return (NULL);
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	while (i < len)
	{
		var_name[i] = str[i];
		i++;
	}
	var_name[len] = '\0';
	return (var_name);
}

char	*find_in_env_array(char **env, const char *var_name)
{
	char	*eq_pos;
	int		name_len;
	int		i;

	i = 0;
	if (!env || !var_name)
		return (NULL);
	name_len = ft_strlen(var_name);
	while (env[i])
	{
		eq_pos = ft_strchr(env[i], '=');
		if (eq_pos && (eq_pos - env[i]) == name_len)
		{
			if (ft_strncmp(env[i], var_name, name_len) == 0)
				return (eq_pos + 1);
		}
		i++;
	}
	return (NULL);
}

char	*get_env_var(env_t *env, const char *var_name)
{
	char	*value;

	if (!env || !var_name)
		return (NULL);
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(g_last_exit_status));
	value = find_in_env_array(env->mod, var_name);
	if (value)
		return (value);
	return (find_in_env_array(env->start, var_name));
}
