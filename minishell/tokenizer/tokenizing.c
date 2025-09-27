/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:42:30 by skuik             #+#    #+#             */
/*   Updated: 2025/09/27 14:05:32 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_token(t_token **head, t_token *new_tok)
{
	t_token	*cur;

	cur = *head;
	if (!*head)
	{
		*head = new_tok;
		return ;
	}
	while (cur->next)
		cur = cur->next;
	cur->next = new_tok;
}

bool	is_operator_start(char c)
{
	return (c == '>' || c == '<' || c == '|' || c == '&' || c == ';');
}

size_t	skip_spaces(const char *input, size_t i)
{
	while (input[i] && isspace(input[i]))
		i++;
	return (i);
}

void	append_seg_w_expans(char **result, t_exp_data data, t_env *env)
{
	char	*segment;
	char	*expanded;

	segment = ft_substr(data.input, data.start, data.end - data.start);
	if (data.expand && env)
	{
		expanded = expand_var(segment, env);
		if (expanded)
		{
			*result = ft_strjoin(*result, expanded);
			free(expanded);
		}
		else
			*result = ft_strjoin(*result, segment);
	}
	else
		*result = ft_strjoin(*result, segment);
	free(segment);
}
