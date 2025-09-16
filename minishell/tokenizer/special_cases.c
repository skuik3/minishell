/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:53:15 by skuik             #+#    #+#             */
/*   Updated: 2025/09/16 15:54:59 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *expand_vars(const char *str, env_t *env);

static int check_var_match(char *entry, const char *var)
{
    char *eq;
    int len;

    eq = ft_strchr(entry, '=');
    if (!eq)
        return (0);
    len = eq - entry;
    if (ft_strncmp(entry, var, len) == 0 && var[len] == '\0')
        return (1);
    return (0);
}

char *get_env_from_array(char **arr, const char *var)
{
    char *eq;

    if (!arr || !*arr)
        return (NULL);
    if (check_var_match(*arr, var))
    {
        eq = ft_strchr(*arr, '=');
        return (eq + 1);
    }
    return (get_env_from_array(arr + 1, var));
}

char *get_env_value(env_t *env, const char *var)
{
    if (!env)
        return (NULL);
    char *val = get_env_from_array(env->mod, var);
    if (val)
        return (val);
    return get_env_from_array(env->start, var);
}

int is_var_char(char c, int start)
{
    if (start)
        return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') 
            || (c >= '0' && c <= '9') || c == '_');
}

static int get_var_length(const char *s)
{
    int i;

    i = 0;
    if (!is_var_char(s[i], 1))
        return (0);
    while (s[i] && is_var_char(s[i], 0))
        i++;
    return (i);
}

char *get_varname(const char *s, int *len)
{
    *len = get_var_length(s);
    if (*len == 0)
        return (NULL);
    return (ft_substr(s, 0, *len));
}

static void copy_string_to_buffer(char *dest, char *src, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        dest[i] = src[i];
        i++;
    }
}

char *ft_strjoinch(char *s, char c)
{
    int len;
    char *out;

    len = ft_strlen(s);
    out = malloc(len + 2);
    if (!out)
        return (NULL);
    copy_string_to_buffer(out, s, len);
    out[len] = c;
    out[len + 1] = '\0';
    free(s);
    return (out);
}

static char *handle_regular_char(const char *str, env_t *env)
{
    char *after;

    after = expand_vars(str + 1, env);
    return (ft_strjoinch(after, *str));
}

static char *handle_dollar_sign(const char *str, env_t *env)
{
    char *after;

    after = expand_vars(str + 1, env);
    return (ft_strjoinch(after, '$'));
}

static char *get_env_var_value(char *var, env_t *env)
{
    char *val;

    val = get_env_value(env, var);
    if (val)
        return (ft_strdup(val));
    return (ft_strdup(""));
}

static char *handle_variable_expansion(const char *str, env_t *env, int len)
{
    char *var;
    char *before;
    char *after;
    char *res;

    var = get_varname(str + 1, &len);
    before = get_env_var_value(var, env);
    free(var);
    after = expand_vars(str + 1 + len, env);
    res = ft_strjoin(before, after);
    free(before);
    free(after);
    return (res);
}

char *expand_vars(const char *str, env_t *env)
{
    int len;
    char *var;

    if (!str || *str == '\0')
        return (ft_strdup(""));
    if (*str != '$')
        return (handle_regular_char(str, env));
    var = get_varname(str + 1, &len);
    if (!var)
        return (handle_dollar_sign(str, env));
    free(var);
    return (handle_variable_expansion(str, env, len));
}