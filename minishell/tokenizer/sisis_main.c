/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sisis_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:42:31 by skuik             #+#    #+#             */
/*   Updated: 2025/07/23 19:23:15 by skuik            ###   ########.fr       */
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

void print_command(t_command *cmd, int index)
{
   
	printf("Command %d: %s\n", index, cmd->command);
	print_list(cmd->arguments, "Args");
	print_list(cmd->redir_in, "Redir In");
	print_list(cmd->redir_out, "Redir Out");
	if (cmd->heredoc)
		printf("  Heredoc: [%s]\n", cmd->heredoc);
	if (cmd->append)
		printf("  Append: [%s]\n", cmd->append);
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

	tokens = tokenize(line);
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

// int sisis_main(void)
// {
// 	char *line = NULL;
// 	size_t bufsize = 0;
// 	ssize_t n;

// 	puts("To quit use: 'exit', Ctrl-D or Ctrl-Q");
// 	while (1)
// 	{
// 		printf("minishell$ ");
// 		fflush(stdout);
// 		n = getline(&line, &bufsize, stdin);
// 		if (is_exit_input(line, n))
// 			break;
// 		if (n && line[n - 1] == '\n')
// 			line[n - 1] = '\0';
// 		if (line[0] != '\0')
// 			run_shell_line(line);
// 	}

// 	free(line);
// 	printf("exit\n");
// 	return (0);
// }
