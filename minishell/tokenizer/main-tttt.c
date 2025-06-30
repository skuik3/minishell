/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-tttt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:28:08 by skuik             #+#    #+#             */
/*   Updated: 2025/06/23 14:24:46 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void append_token(t_token **head, t_token *new_tok)
{
    if (!*head)
    {
        *head = new_tok;
        return;
    }
    t_token *cur = *head;
    while (cur->next)
        cur = cur->next;
    cur->next = new_tok;
}

static bool is_operator_start(char c)
{
    return (c == '>' || c == '<' || c == '|' || c == '&' || c == ';');
}

static size_t skip_spaces(const char *input, size_t i)
{
    while (input[i] && isspace(input[i]))
        i++;
    return (i);
}

static size_t parse_quoted(const char *input, size_t i, t_token **tokens)
{
    char quote = input[i++];
    size_t start = i;
    
    while (input[i] && input[i] != quote)
        i++;
    if (input[i] == quote)
        append_token(tokens, new_token(&input[start], i - start, T_WORD));
    else
        append_token(tokens, new_token(&input[start], i - start, T_WORD));
    if (input[i] == quote)
        return (i + 1);
    else
        return (i);
}

static size_t parse_operator(const char *input, size_t i, t_token **tokens)
{
    size_t start = i;
    if ((input[i] == '>' || input[i] == '<' || input[i] == '|' || input[i] == '&')
        && input[i + 1] == input[i])
        i += 2;
    else
        i += 1;
    append_token(tokens, new_token(&input[start], i - start, get_token_type(&input[start])));
    return (i);
}

static size_t parse_word(const char *input, size_t i, t_token **tokens)
{
    size_t start = i;
    while (input[i] && !isspace(input[i]) && !is_operator_start(input[i]))
        i++;
    append_token(tokens, new_token(&input[start], i - start, T_WORD));
    return (i);
}

static t_token *tokenize(const char *input)
{
    t_token *tokens = NULL;
    size_t i = 0;

    while (input[i])
    {
        i = skip_spaces(input, i);
        if (!input[i])
            break;
        if (input[i] == '"' || input[i] == '\'')
            i = parse_quoted(input, i, &tokens);
        else if (is_operator_start(input[i]))
            i = parse_operator(input, i, &tokens);
        else
            i = parse_word(input, i, &tokens);
    }
    return (tokens);
}

void print_tokens(t_token *head)
{
    int i;
    
    i = 0;
    while (head)
    {
        printf("Token[%d]: %-10s\t(Type: %d)\n", i++, head->value, head->type);
        head = head->next;
    }
}

void free_tokens(t_token *head)
{
    while (head)
    {
        t_token *tmp = head;
        head = head->next;
        free(tmp->value);
        free(tmp);
    }
}

int main(int argc, char *argv[])
{
    int i;

    i = 1;
    if (argc < 2)
    {
        fprintf(stderr, "You should: %s [command args...]\n", argv[0]);
        return (1);
    }
    printf("Args given: %d\n", argc - 1);
    while (i < argc)
    {
        t_token_type token_type = get_token_type(argv[i]);
        printf("Token %d: %s\t(Type: %s)\n", i, argv[i], token_type_to_string(token_type));
        i++;
    }
    return (0);
}



// int determine_token_type(const char *token)
// {
//     int is_numeric = 1;
//     int is_alpha = 1;

//     for (int i = 0; token[i] != '\0'; i++)
//     {
//         if (!isdigit(token[i]))
//             is_numeric = 0;
//         if (!isalpha(token[i]))
//             is_alpha = 0;
//     }

//     if (is_numeric)
//         return 1; // Numeric type
//     else if (is_alpha)
//         return 2; // Alphabetic type
//     else
//         return 3; // Other type
// }

// int main(int argc, char *argv[])
// {
//     int i;

//     i = 1;
//     if (argc < 2)
//     {
//         fprintf(stderr, "You should: %s [command args...]\n", argv[0]);
//         return 1;
//     }
//     printf("Args given: %d\n", argc - 1);
//     while (i < argc)
//     {
//         int token_type = determine_token_type(argv[i]);
//         printf("Token %d: %s\t(Type: %d)\n", i, argv[i], token_type);
//         i++;
//     }
//     return 0;
// }

// // int main(int argc, char *argv[])
// // {
// //     int i;
    
// //     i = 1;
// //     if (argc < 2)
// //     {
// //         fprintf(stderr, "You should: %s [command args...]\n", argv[0]);
// //         return 1;
// //     }
// //     printf("Args given: %d\n", argc - 1);
// //     while (i < argc)
// //     {
// //         printf("Token %d: %s\n", i, argv[i]);
// //         i++;
// //     }
// //     return (0);
// // }
