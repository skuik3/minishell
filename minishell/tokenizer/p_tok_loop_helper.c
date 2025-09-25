/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_tok_loop_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:27:01 by skuik             #+#    #+#             */
/*   Updated: 2025/09/25 11:12:25 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_redir_token(t_token *tok, t_cmd_builder *b)
{
	t_redir	*r;

	if (!tok->next)
		return ;
	if (tok->type == T_REDIR_IN || tok->type == T_REDIR_HEREDOC)
		r = new_redir(tok->next, get_redir_type_from_token(tok->type));
	else if (tok->type == T_REDIR_OUT || tok->type == T_REDIR_APPEND)
		r = new_redir(tok->next, get_redir_type_from_token(tok->type));
	else
		return ;
	if (r)
		add_redir_to_list(tok, r, b);
}

bool	is_invalid_token(t_token *tok)
{
	if (!tok)
		return (true);
	if (tok->type == T_PIPE && (!tok->next || tok->next->type != T_WORD))
		return (true);
	if (tok->type == T_REDIR_IN && (!tok->next || tok->next->type != T_WORD))
		return (true);
	if (tok->type == T_REDIR_OUT && (!tok->next || tok->next->type != T_WORD))
		return (true);
	if (tok->type == T_REDIR_HEREDOC && (!tok->next
			|| tok->next->type != T_WORD))
		return (true);
	if (tok->type == T_REDIR_APPEND && (!tok->next
			|| tok->next->type != T_WORD))
		return (true);
	return (false);
}

bool	init_cmd_builder(t_cmd_builder *b, t_command **out)
{
	*out = NULL;
	b->cmd = malloc(sizeof(t_command));
	if (!b->cmd)
		return (false);
	ft_memset(b->cmd, 0, sizeof(t_command));
	b->args = NULL;
	b->redir_in = NULL;
	b->redir_out = NULL;
	return (true);
}

char	*get_token_value(t_token *tok, env_t *env)
{
	(void)env;
	if (!tok || !tok->value)
		return (ft_strdup(""));
	return (ft_strdup(tok->value));
}
