# minishell
Minishell

Minishell is a 42 Prague team project that consists of creating a basic Unix shell in C, inspired by Bash.
The project focuses on process management, pipes, redirections, signal handling, and environment variables.

Features

Interactive prompt with command history

Execution of system binaries via $PATH and local executables

Built-in commands:

echo (-n)

cd

pwd

export

unset

env

exit

Pipes (|)

Redirections:

< input

> output

>> output (append)

<< heredoc (no history update)

Environment variable expansion ($VAR, $?)

Signal handling:

ctrl-C → new prompt

ctrl-D → exit

ctrl-\ → ignored

Usage
make
./minishell

Constraints

Only one global variable (used for signal handling)

No support for \, ;, &&, ||, or wildcards

Unclosed quotes are not interpreted

readline() leaks are allowed by the subject

Authors

Made by you & teammate
42 Prague
