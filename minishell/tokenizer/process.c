/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:28:08 by skuik             #+#    #+#             */
/*   Updated: 2025/09/25 11:05:16 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

const char	*token_type_to_string(t_token_type type)
{
	if (type == T_WORD)
		return ("WORD");
	if (type == T_PIPE)
		return ("PIPE");
	if (type == T_OR)
		return ("OR");
	if (type == T_AND)
		return ("AND");
	if (type == T_BG)
		return ("BG");
	if (type == T_END)
		return ("END");
	return (0);
}

const char	*redir_type_to_string(t_redir_type type)
{
	if (type == REDIR_IN)
		return ("<");
	if (type == REDIR_OUT)
		return (">");
	if (type == REDIR_APPEND)
		return (">>");
	if (type == REDIR_HEREDOC)
		return ("<<");
	return (0);
}

static t_token_type	get_t_type_from_redir(t_redir_type rtype,
		char *arg, size_t len)
{
	if (rtype != 0)
		return (T_WORD);
	return (get_token_type_len(arg, len));
}

t_token	*argv_to_token_list(int argc, char **argv)
{
	t_token			*head;
	int				i;
	size_t			len;
	t_redir_type	rtype;
	t_token_type	tp;

	head = NULL;
	i = 1;
	while (i < argc)
	{
		len = ft_strlen(argv[i]);
		rtype = get_redir_type(argv[i], len);
		tp = get_t_type_from_redir(rtype, argv[i], len);
		append_token(&head, new_token(argv[i], len, tp));
		i++;
	}
	return (head);
}
