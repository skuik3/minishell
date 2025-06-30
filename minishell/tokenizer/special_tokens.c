/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:53:23 by skuik             #+#    #+#             */
/*   Updated: 2025/06/12 11:54:58 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int seperate(char *c)
{
	if (!ft_strncmp(c, "&&", 2) || *c == ' ' || *c == '\t'
		|| *c == '<' || *c == '>' || *c == '|' || *c == '(' || *c == ')')
		return (1);
	return (0);
}

void skip_leading_whitespace(char **str)
{
    while (**str == ' ' || **str == '\t')
        (*str)++;
}

bool	skip_quoted_section(char *line, size_t *index)
{
    char	quote_char;
    size_t	start_pos = *index;

    if (!line || !line[*index])
        return (false);
    quote_char = line[*index];
    if (quote_char != '\'' && quote_char != '\"')
        return (false);
    (*index)++;
    while (line[*index] && line[*index] != quote_char)
        (*index)++;
    if (line[*index] == quote_char)
    {
        (*index)++;
        return (true);
    }
    *index = start_pos;
    return (false);
}

void error(char c)
{
    
}