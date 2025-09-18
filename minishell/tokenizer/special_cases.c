/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:53:15 by skuik             #+#    #+#             */
/*   Updated: 2025/09/18 20:18:52 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_valid_var_char(char c, int is_first)
{
    if (is_first)
        return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') 
            || (c >= '0' && c <= '9') || c == '_');
}

static int get_var_name_len(const char *str)
{
    int len;

    len = 0;
    if (!str || !is_valid_var_char(str[0], 1))
        return (0);
    while (str[len] && is_valid_var_char(str[len], 0))
        len++;
    return (len);
}

static char *extract_var_name(const char *str, int len)
{
    char *var_name;
    int i;

    if (len <= 0)
        return (NULL);
    var_name = malloc(len + 1);
    if (!var_name)
        return (NULL);
    i = 0;
    while (i < len)
    {
        var_name[i] = str[i];
        i++;
    }
    var_name[len] = '\0';
    return (var_name);
}

static char *find_in_env_array(char **env, const char *var_name)
{
    char *eq_pos;
    int name_len;
    int i;

    if (!env || !var_name)
        return (NULL);
    name_len = ft_strlen(var_name);
    i = 0;
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

static char *get_env_var(env_t *env, const char *var_name)
{
    char *value;

    if (!env || !var_name)
        return (NULL);
    value = find_in_env_array(env->mod, var_name);
    if (value)
        return (value);
    return (find_in_env_array(env->start, var_name));
}

static char *join_expansion_parts(char *before, char *expansion, char *after)
{
    char *temp;
    char *result;

    temp = ft_strjoin(before, expansion);
    if (!temp)
        return (NULL);
    result = ft_strjoin(temp, after);
    free(temp);
    return (result);
}

char *expand_variables(const char *input, env_t *env)
{
    char *dollar_pos;
    char *before;
    char *var_name;
    char *var_value;
    char *after;
    char *result;
    int var_len;

    if (!input || !env)
        return (ft_strdup(input ? input : ""));
    dollar_pos = ft_strchr(input, '$');
    if (!dollar_pos)
        return (ft_strdup(input));
    before = ft_substr(input, 0, dollar_pos - input);
    var_len = get_var_name_len(dollar_pos + 1);
    if (var_len == 0)
    {
        result = ft_strjoin(before, "$");
        return (result);
    }
    var_name = extract_var_name(dollar_pos + 1, var_len);
    var_value = get_env_var(env, var_name);
    after = expand_variables(dollar_pos + 1 + var_len, env);
    result = join_expansion_parts(before, var_value ? var_value : "", after);
    free(var_name);
    free(after);
    return (result);
}