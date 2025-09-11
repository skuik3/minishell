/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sisis_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:42:31 by skuik             #+#    #+#             */
/*   Updated: 2025/09/11 09:04:42 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_list(char **arr, const char *label)
{
	int i;

	i = 0;
	if (!arr)
		return;
	printf("  %s: ", label);
	while (arr[i])
	{
		printf("[%s] ", arr[i]);
		i++;
	}
	printf("\n");
}

//only for seeing it now
void print_redirs(t_redir **redirs, int count, const char *label)
{
	int i;

	if (!redirs || count == 0)
		return;
	printf("  %s:\n", label);
	for (i = 0; i < count; i++)
	{
		if (redirs[i]->type == REDIR_IN)
			printf("    Input: [%s]\n", redirs[i]->filename);
		else if (redirs[i]->type == REDIR_OUT)
			printf("    Output: [%s]\n", redirs[i]->filename);
		else if (redirs[i]->type == R_APPEND)
			printf("    Append: [%s]\n", redirs[i]->filename);
		else if (redirs[i]->type == R_HEREDOC)
			printf("    Heredoc: [%s]\n", redirs[i]->filename);
	}
}

void print_command(t_command *cmd, int index)
{
	printf("Command %d: %s\n", index, cmd->cmd_str ? cmd->cmd_str : "(null)");
	print_list(cmd->args, "Args");
	print_redirs(cmd->redir_in, cmd->redir_in_count, "Input Redirections");
	print_redirs(cmd->redir_out, cmd->redir_out_count, "Output Redirections");
}

void print_cmd(t_command *cmd)
{
	int i;

	i = 1;
	while (cmd)
	{
		print_command(cmd, i);
		i++;
		cmd = cmd->next;
	}
	printf("%d commands in pipeline.\n", i - 1);
}

int is_exit_input(const char *line, ssize_t n)
{
	if (n == -1)
		return (1);
	if (n == 2 && line[0] == '\x11')
		return (1);
	if (!strncmp(line, "exit", 4))
		return (1);
	return (0);
}

t_command *run_shell_line(char *line)
{
	t_token *tokens;
	t_command *cmd_list = NULL;

	printf("Input line: [%s]\n", line);
	tokens = tokenize(line);
	printf("Tokens:\n");
	if (!tokens)
	{
		fprintf(stderr, "Tokenization failed.\n");
		return (NULL);
	}
	if (!init_commands(&cmd_list, tokens))
	{
		fprintf(stderr, "Parsing failed.\n");
		free_tokens(tokens);
		return (NULL);
	}
	print_cmd(cmd_list);
	free_tokens(tokens);
	return (cmd_list);
}
