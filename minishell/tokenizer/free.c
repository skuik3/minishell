/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:54:48 by skuik             #+#    #+#             */
/*   Updated: 2025/09/18 19:58:35 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(t_token *head)
{
	t_token *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_redir_array(t_redir **arr, int count)
{
	if (count <= 0 || !arr)
		return;

	t_redir **current = arr;
	while (count--)
	{
		if (*current)
		{
			free((*current)->filename);
			free(*current);
		}
		current++;
	}
	free(arr);
}

void	free_array(char **arr)
{
	if (!arr)
		return;

	char **current = arr;
	while (*current)
	{
		free(*current);
		current++;
	}
	free(arr);
}

void	free_cmd(t_command *cmd)
{
	t_command *next;

	while (cmd)
	{
		next = cmd->next;
		free_array(cmd->arguments);

		free_redir_array(cmd->redir_in, cmd->redir_in_count);
		free_redir_array(cmd->redir_out, cmd->redir_out_count);

		free(cmd);
		cmd = next;
	}
}

void	free_list(t_list *list)
{
	t_list *temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
}

void	free_string_list(t_list *list)
{
	t_list *temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->content)
			free(temp->content);
		free(temp);
	}
}

void	free_cmd_builder(t_cmd_builder *builder)
{
	if (!builder)
		return ;

	free_cmd(builder->cmd);
	free_list(builder->args);
	free_list(builder->redir_in);
	free_list(builder->redir_out);
	free(builder);
}
