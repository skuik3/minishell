# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 12:00:13 by skuik             #+#    #+#              #
#    Updated: 2025/09/05 15:23:31 by anezkahavra      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = tokenizer/sisis_main.c \
      tokenizer/free.c \
	  tokenizer/parse_pipes.c \
	  tokenizer/parse_tok_loop.c \
	  tokenizer/parse_token.c \
	  tokenizer/parser_handle_token.c \
	  tokenizer/process.c \
	  tokenizer/special_cases.c \
	  tokenizer/tokenizing.c \
	  tokenizer/helper_funcs/ft_strjoin.c\
	  tokenizer/helper_funcs/ft_strdup.c\
	  func_anezka/builtins/cd_pwd.c\
	  func_anezka/builtins/echo.c\
	  func_anezka/builtins/env.c\
	  func_anezka/builtins/export.c\
	  func_anezka/builtins/unset.c\
	  func_anezka/main/command_find.c\
	  func_anezka/main/libft_utils.c\
	  func_anezka/nonbuiltins/nonbuiltins.c\
	  main_test.c\
	  func_anezka/builtins/export_utils.c\
	  func_anezka/main/env_variables.c\
	  func_anezka/nonbuiltins/pipes.c\
	  func_anezka/main/forks.c\
	  func_anezka/nonbuiltins/redirect_out.c\
	  func_anezka/nonbuiltins/redirect_in.c\
	  func_anezka/nonbuiltins/heredoc.c\
	  func_anezka/nonbuiltins/heredoc_multipl.c\
	  func_anezka/main/signals.c\
	  get_next_line/get_next_line.c\
	  get_next_line/get_next_line_utils.c\
	  func_anezka/main/big_struct.c\



OBJ = $(SRC:.c=.o)
CC = cc
#FLAGS = -Wall -Wextra -Werror
FLAGS = -I/usr/local/opt/readline/include
LIBS = -pthread -lreadline -L/usr/local/opt/readline/lib

all: $(NAME)

$(NAME): $(OBJ)
	cc $(FLAGS) $(LIBS) $(OBJ) -o $(NAME)

%.o: %.c
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
