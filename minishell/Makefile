# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skuik <skuik@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 12:00:13 by skuik             #+#    #+#              #
#    Updated: 2025/09/24 14:22:26 by skuik            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c\
	func/builtins/cd_pwd.c\
	func/builtins/echo.c\
	func/builtins/env.c\
	func/builtins/export.c\
	func/builtins/export_utils.c\
	func/builtins/unset.c\
	func/builtins/unset_utils.c\
	func/builtins/exit.c\
	func/exec/big_struct.c\
	func/exec/command_find.c\
	func/exec/single_command.c\
	func/exec/env_variables.c\
	func/exec/forks.c\
	func/exec/free.c\
	func/exec/libft_utils.c\
	func/exec/signals.c\
	func/exec/utils.c\
	func/exec/builtins_commands.c\
	func/nonbuiltins/heredoc_utils.c\
	func/nonbuiltins/heredoc.c\
	func/nonbuiltins/nonbuiltins.c\
	func/nonbuiltins/pipes.c\
	func/nonbuiltins/redirect_in.c\
	func/nonbuiltins/redirect_out.c\
	tokenizer/alloc_stuff.c\
	tokenizer/free.c\
	tokenizer/free2.c\
	tokenizer/get_type.c\
	tokenizer/handle_and_check.c\
	tokenizer/parse_pipes.c\
	tokenizer/parse_tok_loop.c\
	tokenizer/parse_token.c\
	tokenizer/parser_handle_token.c\
	tokenizer/process.c\
	tokenizer/special_case.c\
	tokenizer/special_case2.c\
	tokenizer/special_case3.c\
	tokenizer/tokenizing.c\
	tokenizer/tokenizing2.c\
	tokenizer/sisis_main.c\
	helper_funcs/ft_atoi.c\
	helper_funcs/ft_bzero.c\
	helper_funcs/ft_calloc.c\
	helper_funcs/ft_isascii.c\
	helper_funcs/ft_isdigit.c\
	helper_funcs/ft_isprint.c\
	helper_funcs/ft_itoa.c\
	helper_funcs/ft_memchr.c\
	helper_funcs/ft_memcmp.c\
	helper_funcs/ft_memcpy.c\
	helper_funcs/ft_memmove.c\
	helper_funcs/ft_memset.c\
	helper_funcs/ft_putchar_fd.c\
	helper_funcs/ft_putendl_fd.c\
	helper_funcs/ft_putnbr_fd.c\
	helper_funcs/ft_str_is_alpha.c\
	helper_funcs/ft_str_is_lowercase.c\
	helper_funcs/ft_str_is_numeric.c\
	helper_funcs/ft_str_is_printable.c\
	helper_funcs/ft_str_is_uppercase.c\
	helper_funcs/ft_strchr.c\
	helper_funcs/ft_strjoin.c\
	helper_funcs/ft_striteri.c\
	helper_funcs/ft_strmapi.c\
	helper_funcs/ft_strnstr.c\
	helper_funcs/ft_strrchr.c\
	helper_funcs/ft_strtrim.c\
	helper_funcs/ft_substr.c\
	helper_funcs/ft_strncmp.c\
	helper_funcs/get_next_line_utils.c\
	helper_funcs/get_next_line.c\
	

OBJ = $(SRC:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror
FLAGS = -I/usr/local/opt/readline/include -g
LIBS = -pthread -lreadline -lreadline -L/usr/local/opt/readline/lib -lncurses


OBJ = $(SRC:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror -I/usr/local/opt/readline/include -g
LIBS = -pthread -L/usr/local/opt/readline/lib -lreadline -lncurses

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LIBS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

val:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp.supp ./minishell

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
