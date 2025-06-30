/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-t.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:58:48 by skuik             #+#    #+#             */
/*   Updated: 2025/06/20 18:44:18 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//reed the input from the user
//so the i should take the input form user like (echo -n "hello")
//scan the line char by char
//and i need to split up the content into tokens
//i need to ignore all the spaces (exept the spaces in "" '')
//but also i need to know when entering and exiting ('' "")
//so start with empty and additionally push the individual tokens one by one
//if i pushed all tokens to the list
//i can reset token buffer and keep adding chars

int is_invalid_input(const char *input)
{
    if (input == NULL || input[0] == '\0')
        return (1);
    while (*input == ' ' || *input == '\t' || *input == '\n')
        input++;
    return (*input == '\0');
}

char *copy_input(const char *input)
{
    char *copy;
    
    copy = strdup(input);
    return (copy);
}


void free_tokens(char **tokens, int count)
{
    int i = 0;
    while (i < count)
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

char **split_into_tokens(char *input)
{
    int i;
    char **tokens;
    char *token;

    i = 0;
    tokens = malloc(sizeof(char *) * (MAX_TOKENS + 1));
    if (!tokens)
        return (NULL);
    token = strtok(input, " \t\n");
    while (token != NULL && i < MAX_TOKENS)
    {
        tokens[i] = strdup(token);
        if (!tokens[i])
        {
            free_tokens(tokens, i);
            return (NULL);
        }
        i++;
        token = strtok(NULL, " \t\n");
    }
    tokens[i] = NULL;
    return (tokens);
}

char **tokenize_input(const char *input)
{
    char *copy;
    char *trimmed;
    char **tokens;
    
    if (is_invalid_input(input))
        return (NULL);
    copy = copy_input(input);
    if (!copy)
        return (NULL);
    trimmed = skip_leading_whitespace(copy);
    if (*trimmed == '\0')
    {
        free(copy);
        return (NULL);
    }
    tokens = split_into_tokens(trimmed);
    free(copy);
    return tokens;
}

int main(int argc, char *argv[])
{
    char **tokens;

    if (argc < 2)
    {
        printf("Usage: %s <input_string>\n", argv[0]);
        return (1);
    }
    tokens = tokenize_input(argv[1]);
    if (tokens)
    {
        int i = 0;
        while (tokens[i])
        {
            printf("Token[%d]: %s\n", i, tokens[i]);
            free(tokens[i]);
            i++;
        }
        free(tokens);
    }
    else
    {
        printf("No tokens found.\n");
    }
    return (0);
}



//t_token *new_token(char *value, t_token_type type) //Create each token during tokenization.
//void add_token(t_token **list, t_token *new) //Add each token to the list (at the end or with tail pointer).
