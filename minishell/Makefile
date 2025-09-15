# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anezka <anezka@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 12:00:13 by skuik             #+#    #+#              #
#    Updated: 2025/09/15 09:52:32 by anezka           ###   ########.fr        #
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
	func/exec/big_struct.c\
	func/exec/command_find.c\
	func/exec/env_variables.c\
	func/exec/forks.c\
	func/exec/free.c\
	func/exec/libft_utils.c\
	func/exec/signals.c\
	func/exec/utils.c\
	func/nonbuiltins/heredoc_multiple.c\
	func/nonbuiltins/heredoc.c\
	func/nonbuiltins/nonbuiltins.c\
	func/nonbuiltins/pipes.c\
	func/nonbuiltins/redirect_in.c\
	func/nonbuiltins/redirect_out.c\
	tokenizer/free.c\
	tokenizer/parse_pipes.c\
	tokenizer/parse_tok_loop.c\
	tokenizer/parse_token.c\
	tokenizer/parse_handle_token.c\
	tokenizer/process.c\
	tokenizer/special_cases.c\
	tokenizer/tokenizing.c\
	tokenizer/helper_funcs/ft_atoi.c\
	tokenizer/helper_funcs/ft_bzero.c\
	tokenizer/helper_funcs/ft_calloc.c\
	tokenizer/helper_funcs/ft_isalnum.c\
	tokenizer/helper_funcs/ft_isalpha.c\
	tokenizer/helper_funcs/ft_isascii.c\
	tokenizer/helper_funcs/ft_isdigit.c\
	tokenizer/helper_funcs/ft_isprint.c\
	tokenizer/helper_funcs/ft_itoa.c\
	tokenizer/helper_funcs/ft_memchr.c\
	tokenizer/helper_funcs/ft_memcmp.c\
	tokenizer/helper_funcs/ft_memcpy.c\
	tokenizer/helper_funcs/ft_memmove.c\
	tokenizer/helper_funcs/ft_memset.c\
	tokenizer/helper_funcs/ft_putchar_fd.c\
	tokenizer/helper_funcs/ft_putendl_fd.c\
	tokenizer/helper_funcs/ft_putnbr_fd.c\
	tokenizer/helper_funcs/ft_putstr_fd.c\
	tokenizer/helper_funcs/ft_split.c\
	tokenizer/helper_funcs/ft_str_is_lowercase.c\
	tokenizer/helper_funcs/ft_str_is_numeric.c\
	tokenizer/helper_funcs/ft_str_is_printable.c\
	tokenizer/helper_funcs/ft_str_is_uppercase.c\
	tokenizer/helper_funcs/ft_strchr.c\
	tokenizer/helper_funcs/ft_strdup.c\
	tokenizer/helper_funcs/ft_striteri.c\
	tokenizer/helper_funcs/ft_strjoin.c\
	tokenizer/helper_funcs/ft_strlcat.c\
	tokenizer/helper_funcs/ft_strlcpy.c\
	tokenizer/helper_funcs/ft_strlen.c\
	tokenizer/helper_funcs/ft_strmapi.c\
	tokenizer/helper_funcs/ft_strncmp.c\
	tokenizer/helper_funcs/ft_strnstr.c\
	tokenizer/helper_funcs/ft_strrchr.c\
	tokenizer/helper_funcs/ft_strtrim.c\
	tokenizer/helper_funcs/ft_substr.c\
	tokenizer/helper_funcs/ft_tolower.c\
	tokenizer/helper_funcs/ft_toupper.c\
	tokenizer/helper_funcs/get_next_line_utils.c\
	tokenizer/helper_funcs/get_next_line.c\
	

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

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
