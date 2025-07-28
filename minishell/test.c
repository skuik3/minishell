
// #include "minishell.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// // // Modified environment structure
// // typedef struct environment_variables {
// //     char **start;  // Original environment variables
// //     char **mod;    // Modified environment variables
// // } env_t;

// // // Command structure (unchanged)
// // typedef struct s_command {
// //     char *command;
// //     char **arguments;
// //     char **redir_in;
// //     char **redir_out;
// //     char *heredoc;
// //     char *append;
// //     struct s_command *next;
// //     env_t *envar;
// // } t_command;

// // Helper function to count environment variables
// size_t count_env_vars(char **env) {
//     size_t count = 0;
//     while (*env) {
//         count++;
//         env++;
//     }
//     return count;
// }

// /**
//  * Creates a new environment structure with synchronized start/mod arrays
//  */
// env_t *create_environment(char *envp[]) {
//     env_t *env = malloc(sizeof(env_t));
//     if (!env) return NULL;

//     int count = count_env_vars(envp);

//     // Allocate memory for both arrays
//     env->start = calloc(count + 1, sizeof(char *));
//     env->mod = calloc(count + 1, sizeof(char *));
    
//     if (!env->start || !env->mod) {
//         free(env->start);
//         free(env->mod);
//         free(env);
//         return NULL;
//     }

//     // Copy environment variables to both arrays
//     char **start = env->start;
//     char **mod = env->mod;
//     for (char **env = envp; *env; env++) {
//         *start = strdup(*env);
//         *mod = strdup(*env);
//         if (!*start || !*mod) {
//             free_environment(env);
//             return NULL;
//         }
//         start++;
//         mod++;
//     }

//     return env;
// }

// /**
//  * Modifies an environment variable and keeps both versions
//  */
// int modify_environment(env_t *env, const char *key, const char *value) {
//     if (!env || !key || !value) return 0;

//     // Find existing entry
//     char **start = env->start;
//     char **mod = env->mod;
//     while (*start && strchr(*start, '=') && strcmp(strchr(*start, '='), key)) {
//         start++;
//         mod++;
//     }

//     // Modify mod array
//     if (*mod) {
//         free(*mod);
//         *mod = malloc(strlen(key) + strlen(value) + 2);  // +2 for '=' and '\0'
//         if (!*mod) return 0;
//         sprintf(*mod, "%s=%s", key, value);
//     } else {
//         // Handle adding new variables
//         size_t len = sizeof(char *) * (count_env_vars(env->start) + 2);
//         env->start = realloc(env->start, len);
//         env->mod = realloc(env->mod, len);
//         if (!env->start || !env->mod) return 0;
        
//         *start = strdup(key);
//         *mod = malloc(strlen(key) + strlen(value) + 2);
//         if (!*start || !*mod) return 0;
//         sprintf(*mod, "%s=%s", key, value);
//     }

//     return 1;
// }

// /**
//  * Frees the environment structure
//  */
// void free_environment(env_t *env) {
//     if (!env) return;

//     // Free start array
//     char **ptr = env->start;
//     while (*ptr) {
//         free(*ptr);
//         ptr++;
//     }
//     free(env->start);

//     // Free mod array
//     ptr = env->mod;
//     while (*ptr) {
//         free(*ptr);
//         ptr++;
//     }
//     free(env->mod);

//     free(env);
// }

// /**
//  * Creates a command structure from a command line string
//  */
// t_command *parse_input(const char *line) {
//     t_command *cmd = malloc(sizeof(t_command));
//     if (!cmd) return NULL;

//     cmd->command = NULL;
//     cmd->arguments = NULL;
//     cmd->redir_in = NULL;
//     cmd->redir_out = NULL;
//     cmd->heredoc = NULL;
//     cmd->append = NULL;
//     cmd->next = NULL;
//     cmd->envar = NULL;

//     // Parse the line into command and arguments
//     char *cmd_str = strdup(line);
//     if (!cmd_str) {
//         free(cmd);
//         return NULL;
//     }

//     // Split line into parts
//     char *token = strtok(cmd_str, " ");
//     if (!token) {
//         free(cmd_str);
//         free(cmd);
//         return NULL;
//     }

//     // Set command
//     cmd->command = token;

//     // Count remaining tokens
//     int argc = 0;
//     char *tmp = strtok(NULL, " ");
//     while (tmp && strcmp(tmp, "|") != 0 && strcmp(tmp, ";") != 0) {
//         argc++;
//         tmp = strtok(NULL, " ");
//     }

//     // Allocate arguments array
//     if (argc > 0) {
//         cmd->arguments = malloc(sizeof(char *) * (argc + 1));
//         if (!cmd->arguments) {
//             free(cmd_str);
//             free(cmd);
//             return NULL;
//         }
//         cmd->arguments[argc] = NULL;

//         token = strtok(cmd_str, " ");
//         token = strtok(NULL, " ");
//         int i = 0;
//         while (token && strcmp(token, "|") != 0 && strcmp(token, ";") != 0 && i < argc) {
//             cmd->arguments[i++] = token;
//             token = strtok(NULL, " ");
//         }
//     }

//     free(cmd_str);
//     return cmd;
// }

// /**
//  * Frees all memory allocated for a command structure
//  */
// void free_command(t_command *cmd) {
//     if (!cmd) return;

//     free(cmd->command);

//     if (cmd->arguments) {
//         char **arg = cmd->arguments;
//         while (*arg) {
//             free(*arg);
//             arg++;
//         }
//         free(cmd->arguments);
//     }

//     if (cmd->redir_in) free(cmd->redir_in);
//     if (cmd->redir_out) free(cmd->redir_out);

//     free(cmd->heredoc);
//     free(cmd->append);

//     if (cmd->envar) {
//         free_environment(cmd->envar);
//     }

//     if (cmd->next) {
//         free_command(cmd->next);
//     }

//     free(cmd);
// }

// /**
//  * Main shell loop
//  */
// int main(int argc, char *argv[], char *envp[]) {
//     char *prompt;
//     t_command *cmd;

//     while (1) {
//         prompt = readline("");
        
//         if (!prompt) {  // EOF or Ctrl+D
//             printf("\n");
//             break;
//         }
        
//         if (*prompt) {
//             add_history(prompt);
            
//             cmd = parse_input(prompt);
//             if (!cmd) {
//                 fprintf(stderr, "Error: Could not allocate memory\n");
//                 continue;
//             }
            
//             cmd->envar = create_environment(envp);
//             what_builtin(cmd);
            
//             free_command(cmd);
//         }
        
//         free(prompt);
//     }
    
//     return 0;
// }