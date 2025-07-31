/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/07/31 14:53:48 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

env_t *adding_env(t_command *cmd, char **envp)
{
    env_t *env;

    (void)cmd; // unused parameter
    env = malloc(sizeof(env_t));
    if (env == NULL)
        return (ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), NULL);
    saving_env(&env->start, envp);
    saving_env(&env->mod, envp);
    return (env);
}

// Basic parsing function to build t_command from readline input
t_command *parse_simple_command(char *input)
{
    t_command *cmd;
    char **tokens;
    char **arguments;
    int token_count, i;

    if (!input || !*input)
        return (NULL);
    
    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), NULL);
    
    // Initialize struct members
    cmd->command = NULL;
    cmd->arguments = NULL;
    cmd->redir_in = NULL;
    cmd->redir_out = NULL;
    cmd->heredoc = NULL;
    cmd->append = NULL;
    cmd->next = NULL;
    cmd->envar = NULL;
    
    // Simple split by spaces (you can improve this later)
    tokens = ft_split(input, ' ');
    if (!tokens || !tokens[0])
    {
        free(cmd);
        return (NULL);
    }
    
    // Count tokens
    token_count = 0;
    while (tokens[token_count])
        token_count++;
    
    // First token is the command
    cmd->command = tokens[0];
    
    // Create arguments array in the format expected by builtin functions
    // [0] = "minishell", [1] = command, [2] = first_arg, [3] = second_arg, etc.
    arguments = malloc(sizeof(char*) * (token_count + 1));
    if (!arguments)
    {
        free(tokens);
        free(cmd);
        return (ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), NULL);
    }
    
    // arguments[0] = ft_strdup("minishell");
    // arguments[1] = ft_strdup(tokens[0]); // command name
    
    // Copy the rest of the tokens as arguments
    for (i = 0; i < token_count; i++)
    {
        arguments[i] = tokens[i + 1];
        // tokens[i] = NULL; // Transfer ownership
    }
    arguments[token_count] = NULL;
    
    cmd->arguments = arguments;
    
    // Clean up the original tokens array
    // free(tokens[0]); // We duplicated this
    // free(tokens);
    
    return (cmd);
}

void free_command(t_command *cmd)
{
    int i;
    
    if (!cmd)
        return;
    
    if (cmd->arguments)
    {
        i = 0;
        while (cmd->arguments[i])
        {
            free(cmd->arguments[i]);
            i++;
        }
        free(cmd->arguments);
    }
    free(cmd);
}

char *ft_strtrim_spaces(char *str)
{
    char *start, *end, *trimmed;
    int len;
    
    if (!str)
        return (NULL);
    
    // Find start (skip leading spaces)
    start = str;
    while (*start && (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r'))
        start++;
    
    // If string is all spaces
    if (*start == '\0')
        return (ft_strdup(""));
    
    // Find end (skip trailing spaces)
    end = str + strlen(str) - 1;
    while (end > start && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r'))
        end--;
    
    // Calculate length and allocate
    len = end - start + 1;
    trimmed = malloc(len + 1);
    if (!trimmed)
        return (NULL);
    
    // Copy trimmed string
    strncpy(trimmed, start, len);
    trimmed[len] = '\0';
    
    return (trimmed);
}

int main(int argc, char *argv[], char *envp[])
{
    char *prompt;
    char **prompt_split;
    t_command *cmd_head = NULL;
    t_command *cmd;
    t_command *cmd_temp;

    (void)argc; // unused parameter
    (void)argv; // unused parameter
    printf("Simple Minishell Test (type 'exit' to quit)\n");
    env_t *env = adding_env(NULL, envp);

    while (1)
    {
        prompt = readline("minishell> ");
        
        if (!prompt) // EOF (Ctrl+D)
            break;
            
        if (*prompt) // Only process non-empty input
        {
            prompt_split = ft_split(prompt, '|');
            for (int i = 0; prompt_split[i]; i++)
            {
                char *original = prompt_split[i];
                prompt_split[i] = ft_strtrim_spaces(prompt_split[i]);
                free(original); // Free the original untrimmed string
                cmd = parse_simple_command(prompt_split[i]);
                cmd->envar = env;

                if (i == 0)
                    cmd_head = cmd;
                else
                    cmd_temp->next = cmd;
                cmd_temp = cmd;
            }
            
            // Print the commands
            cmd = cmd_head;
            for (int i = 0; cmd; i++, cmd = cmd->next)
            {
                printf("Command %d: %s\n", i, cmd->command);
                printf("Arguments: ");
                if (cmd->arguments)
                {
                    for (int j = 0; cmd->arguments[j]; j++)
                    {
                        printf("%s ", cmd->arguments[j]);
                    }
                    printf("\n");
                }
            }
            
            if (cmd_head)
            {
                command_execution(cmd_head);
            }
            
            // Free the entire command list
            cmd = cmd_head;
            while (cmd)
            {
                t_command *next = cmd->next;
                free_command(cmd);
                cmd = next;
            }
            
            // Free prompt_split array
            for (int i = 0; prompt_split[i]; i++)
                free(prompt_split[i]);
            free(prompt_split);
            add_history(prompt);
        }
        
        free(prompt);
    }
    
    printf("\nExiting minishell...\n");
    return (0);
}

