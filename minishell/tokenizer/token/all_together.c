/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_together.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:57:18 by skuik             #+#    #+#             */
/*   Updated: 2025/07/18 23:43:37 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t parse_word(const char *input, size_t i, t_token **tokens)
{
    size_t start = i;
    while (input[i] && !isspace(input[i]) && !is_operator_start(input[i]))
        i++;
    append_token(tokens, new_token(&input[start], i - start, T_WORD));
    return (i);
}

t_token_type get_token_type_len(const char *str, size_t len)
{
    if (len == 2)
    {
        if (strncmp(str, ">>", 2) == 0) return T_APPEND;
        if (strncmp(str, "<<", 2) == 0) return T_HEREDOC;
        if (strncmp(str, "||", 2) == 0) return T_OR;
        if (strncmp(str, "&&", 2) == 0) return T_AND;
    }
    else if (len == 1)
    {
        if (*str == '>') return T_REDIR_OUT;
        if (*str == '<') return T_REDIR_IN;
        if (*str == '|') return T_PIPE;
        if (*str == '&') return T_BG;
        if (*str == ';') return T_END;
    }
    return T_WORD;
}

t_token *new_token(const char *start, size_t len, t_token_type type)
{
    t_token *tok = malloc(sizeof(t_token));
    tok->value = strndup(start, len);
    tok->type = type;
    tok->next = NULL;
    return tok;
}

size_t parse_quoted(const char *input, size_t i, t_token **tokens)
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

void append_token(t_token **head, t_token *new_tok)
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

bool is_operator_start(char c)
{
    return (c == '>' || c == '<' || c == '|' || c == '&' || c == ';');
}

size_t skip_spaces(const char *input, size_t i)
{
    while (input[i] && isspace(input[i]))
        i++;
    return (i);
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

static size_t parse_operator(const char *input, size_t i, t_token **tokens)
{
    size_t start = i;
    t_token_type type;

    if ((input[i] == '>' || input[i] == '<' || input[i] == '|' || input[i] == '&')
        && input[i + 1] == input[i])
    {
        type = get_token_type_len(&input[i], 2);
        i += 2;
    }
    else
    {
        type = get_token_type_len(&input[i], 1);
        i += 1;
    }
    append_token(tokens, new_token(&input[start], i - start, type));
    return (i);
}

t_token *tokenize(const char *input)
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

t_token *argv_to_token_list(int argc, char **argv)
{
    t_token *head = NULL;
    // t_token *tail = NULL;
    int i;
    
    i = 1;
    while (i < argc)
    {
        t_token_type tp = get_token_type_len(argv[i], strlen(argv[i]));
        t_token *n = new_token(argv[i], strlen(argv[i]), tp);
        append_token(&head, n);
        i++;
    }
    return (head);
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

static void process_argv(int argc, char **argv)
{
    if (argc <= 1)
        return;
    printf("Args given: %d\n", argc - 1);
    t_token *toks = argv_to_token_list(argc, argv);
    print_tokens(toks);
    free_tokens(toks);
}

static void token_loop(void)
{
    char *line = NULL;
    size_t buffer_capacity = 0;
    ssize_t n;

    while (1)
    {
        printf("$ ");
        fflush(stdout);
        n = getline(&line, &buffer_capacity, stdin);
        if (n == -1)
            break;
        if (n == 2 && line[0] == '\x11')
            break;
        if (!strncmp(line, "exit", 4))
            break;
        if (n && line[n - 1] == '\n') line[n - 1] = '\0';
        if (line[0] == '\0')
            continue;
        t_token *toks = tokenize(line);
        print_tokens(toks);
        free_tokens(toks);
    }
    free(line);
}

int main(int argc, char **argv)
{
    process_argv(argc, argv);
    puts("To quit program use: 'exit', or Ctrl-D");
    token_loop();
    puts("program exits...");
    return 0;
}




