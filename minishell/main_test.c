/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:15:23 by anezkahavra       #+#    #+#             */
/*   Updated: 2025/09/05 12:19:18 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = 0;

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

// Helper function to check if a token is a redirection operator
int is_redirection(char *token)
{
    if (!token)
        return (0);
    if (strcmp(token, ">") == 0 || strcmp(token, ">>") == 0 ||
        strcmp(token, "<") == 0 || strcmp(token, "<<") == 0)
        return (1);
    return (0);
}

// Helper function to get redirection type
t_redir_type get_redir_type(char *token)
{
    if (strcmp(token, "<") == 0)
        return (REDIR_IN);
    if (strcmp(token, ">") == 0)
        return (REDIR_OUT);
    if (strcmp(token, ">>") == 0)
        return (REDIR_APPEND);
    if (strcmp(token, "<<") == 0)
        return (REDIR_HEREDOC);
    return (REDIR_IN); // fallback
}

// Basic parsing function to build t_command from readline input
t_command *parse_simple_command(char *input)
{
    t_command *cmd;
    char **tokens;
    char **arguments;
    int token_count, i, arg_count = 0;
    int redir_in_count = 0, redir_out_count = 0;
    t_redir *temp_redir_in, *temp_redir_out;

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
    cmd->redir_in_count = 0;
    cmd->redir_out_count = 0;
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
    
    // Temporary arrays to collect redirections
    temp_redir_in = malloc(sizeof(t_redir) * token_count);
    temp_redir_out = malloc(sizeof(t_redir) * token_count);
    if (!temp_redir_in || !temp_redir_out)
    {
        free(tokens);
        free(cmd);
        if (temp_redir_in) free(temp_redir_in);
        if (temp_redir_out) free(temp_redir_out);
        return (ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), NULL);
    }
    
    // Parse tokens and separate command, arguments, and redirections
    i = 0;
    
    // First non-redirection token is the command
    while (i < token_count && is_redirection(tokens[i]))
        i++;
    
    if (i >= token_count)
    {
        // No command found, only redirections
        free(tokens);
        free(cmd);
        free(temp_redir_in);
        free(temp_redir_out);
        return (NULL);
    }
    
    cmd->command = ft_strdup(tokens[i]);
    i++;
    
    // Count non-redirection tokens for arguments
    for (int j = i; j < token_count; j++)
    {
        if (!is_redirection(tokens[j]))
        {
            if (j + 1 < token_count && !is_redirection(tokens[j + 1]))
                arg_count++;
            else if (j + 1 >= token_count)
                arg_count++;
        }
        else
        {
            j++; // Skip the filename after redirection operator
        }
    }
    
    // Allocate arguments array
    arguments = malloc(sizeof(char*) * (arg_count + 1));
    if (!arguments)
    {
        free(tokens);
        free(cmd->command);
        free(cmd);
        free(temp_redir_in);
        free(temp_redir_out);
        return (ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), NULL);
    }
    
    // Parse the rest of the tokens
    arg_count = 0;
    for (int j = i; j < token_count; j++)
    {
        if (is_redirection(tokens[j]))
        {
            // Handle redirection
            if (j + 1 >= token_count)
            {
                // Error: redirection without filename
                printf("minishell: syntax error near unexpected token `newline'\n");
                continue;
            }
            
            t_redir_type type = get_redir_type(tokens[j]);
            char *filename = ft_strdup(tokens[j + 1]);
            
            if (type == REDIR_IN || type == REDIR_HEREDOC)
            {
                temp_redir_in[redir_in_count].filename = filename;
                temp_redir_in[redir_in_count].type = type;
                temp_redir_in[redir_in_count].position = j;
                redir_in_count++;
            }
            else if (type == REDIR_OUT || type == REDIR_APPEND)
            {
                temp_redir_out[redir_out_count].filename = filename;
                temp_redir_out[redir_out_count].type = type;
                temp_redir_out[redir_out_count].position = j;
                redir_out_count++;
            }
            
            j++; // Skip the filename token
        }
        else
        {
            // Regular argument
            arguments[arg_count] = ft_strdup(tokens[j]);
            arg_count++;
        }
    }
    arguments[arg_count] = NULL;
    
    cmd->arguments = arguments;
    
    // Allocate and copy redirection arrays (with null termination)
    if (redir_in_count > 0)
    {
        cmd->redir_in = malloc(sizeof(t_redir*) * (redir_in_count + 1));
        if (cmd->redir_in)
        {
            for (int j = 0; j < redir_in_count; j++)
            {
                cmd->redir_in[j] = malloc(sizeof(t_redir));
                if (cmd->redir_in[j])
                {
                    cmd->redir_in[j]->filename = temp_redir_in[j].filename;
                    cmd->redir_in[j]->type = temp_redir_in[j].type;
                    cmd->redir_in[j]->position = temp_redir_in[j].position;
                }
            }
            // Null terminate the array
            cmd->redir_in[redir_in_count] = NULL;
            cmd->redir_in_count = redir_in_count;
        }
    }
    
    if (redir_out_count > 0)
    {
        cmd->redir_out = malloc(sizeof(t_redir*) * (redir_out_count + 1));
        if (cmd->redir_out)
        {
            for (int j = 0; j < redir_out_count; j++)
            {
                cmd->redir_out[j] = malloc(sizeof(t_redir));
                if (cmd->redir_out[j])
                {
                    cmd->redir_out[j]->filename = temp_redir_out[j].filename;
                    cmd->redir_out[j]->type = temp_redir_out[j].type;
                    cmd->redir_out[j]->position = temp_redir_out[j].position;
                }
            }
            // Null terminate the array
            cmd->redir_out[redir_out_count] = NULL;
            cmd->redir_out_count = redir_out_count;
        }
    }
    
    // Clean up
    free(temp_redir_in);
    free(temp_redir_out);
    
    // Free original tokens
    for (int j = 0; j < token_count; j++)
        free(tokens[j]);
    free(tokens);
    
    return (cmd);
}

void free_command(t_command *cmd)
{
    int i;
    
    if (!cmd)
        return;
    
    if (cmd->command)
        free(cmd->command);
    
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
    
    if (cmd->redir_in)
    {
        for (i = 0; i < cmd->redir_in_count; i++)
        {
            if (cmd->redir_in[i] && cmd->redir_in[i]->filename)
                free(cmd->redir_in[i]->filename);
            free(cmd->redir_in[i]);
        }
        // Note: No need to free the null terminator since it's NULL
        free(cmd->redir_in);
    }
    
    if (cmd->redir_out)
    {
        for (i = 0; i < cmd->redir_out_count; i++)
        {
            if (cmd->redir_out[i] && cmd->redir_out[i]->filename)
                free(cmd->redir_out[i]->filename);
            free(cmd->redir_out[i]);
        }
        // Note: No need to free the null terminator since it's NULL
        free(cmd->redir_out);
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

        //SIGNALS
        signal(SIGINT, handle_signal_main);
        signal(EOF, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        
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
                }
                printf("\n");
                
                // Print input redirections
                if (cmd->redir_in_count > 0)
                {
                    printf("Input redirections: ");
                    for (int j = 0; cmd->redir_in[j] != NULL; j++)
                    {
                        printf("[pos:%d, type:%s, file:%s] ", 
                               cmd->redir_in[j]->position,
                               (cmd->redir_in[j]->type == REDIR_IN) ? "<" : "<<",
                               cmd->redir_in[j]->filename);
                    }
                    printf("\n");
                }
                
                // Print output redirections
                if (cmd->redir_out_count > 0)
                {
                    printf("Output redirections: ");
                    for (int j = 0; cmd->redir_out[j] != NULL; j++) 
                    {
                        printf("[pos:%d, type:%s, file:%s] ", 
                               cmd->redir_out[j]->position,
                               (cmd->redir_out[j]->type == REDIR_OUT) ? ">" : ">>",
                               cmd->redir_out[j]->filename);
                    }
                    printf("\n");
                }
            }
            
            if (cmd_head)
            {
                // g_signal = 0;
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

