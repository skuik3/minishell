/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:54:48 by skuik             #+#    #+#             */
/*   Updated: 2025/09/27 14:44:52 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(t_token *head)
{
	t_token	*tmp;

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
	t_redir	**current;

	current = arr;
	if (count <= 0 || !arr)
		return ;
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
	char	**current;

	current = arr;
	if (!arr)
		return ;
	while (*current)
	{
		free(*current);
		current++;
	}
	free(arr);
}

void	free_cmd(t_command *cmd)
{
	t_command	*next;

	while (cmd)
	{
		next = cmd->next;
		if (cmd->command)
			free(cmd->command);
		free_array(cmd->arguments);
		free_redir_array(cmd->redir_in, cmd->redir_in_count);
		free_redir_array(cmd->redir_out, cmd->redir_out_count);
		free(cmd);
		cmd = next;
	}
}

void	free_list(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
}
