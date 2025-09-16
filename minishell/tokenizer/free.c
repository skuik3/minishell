/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:54:48 by skuik             #+#    #+#             */
/*   Updated: 2025/09/15 11:51:55 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void free_pointer(void *ptr)
// {
//     if (ptr)
//         free(ptr);
// }

// void free_array(void **arr)
// {
//     void **current;

//     if (!arr)
//         return;

//     current = arr;
//     while (*current)
//     {
//         free_pointer(*current);
//         current++;
//     }
//     free_pointer(arr);
// }

// void free_list(t_list *list, void (*free_content)(void *))
// {
//     t_list *temp;

//     while (list)
//     {
//         temp = list->next;
//         if (list->content && free_content)
//             free_content(list->content);
//         free_pointer(list);
//         list = temp;
//     }
// }

// void free_redir(void *redir_ptr)
// {
//     t_redir *redir = (t_redir *)redir_ptr;

//     if (redir)
//     {
//         free_pointer(redir->filename);
//         free_pointer(redir);
//     }
// }

// void free_tokens(void *token_ptr)
// {
//     t_token *token = (t_token *)token_ptr;

//     if (token)
//     {
//         free_pointer(token->value);
//         free_pointer(token);
//     }
// }

// void free_cmd(t_command *cmd)
// {
//     t_command *next;

//     while (cmd)
//     {
//         next = cmd->next;
//         free_array((void **)cmd->arguments);
//         free_array((void **)cmd->redir_in);
//         free_array((void **)cmd->redir_out);
//         free_pointer(cmd);
//         cmd = next;
//     }
// }

// void free_cmd_builder(t_cmd_builder *builder)
// {
//     if (!builder)
//         return;

//     free_cmd(builder->cmd);
//     free_list(builder->args, free_pointer);
//     free_list(builder->redir_in, free_redir);
//     free_list(builder->redir_out, free_redir);
//     free_pointer(builder);
// }

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

void	free_cmd_builder(t_cmd_builder *builder)
{
	if (!builder)
		return ;

	free_cmd(builder->cmd);
	// free_list(builder->args);
	// free_list(builder->redir_in);
	// free_list(builder->redir_out);
	free(builder);
}

