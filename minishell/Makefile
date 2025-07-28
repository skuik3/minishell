# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 12:00:13 by skuik             #+#    #+#              #
#    Updated: 2025/07/28 12:20:03 by anezkahavra      ###   ########.fr        #
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
	  func_anezka/builtins/cd_pwd.c\
	  func_anezka/builtins/echo.c\
	  func_anezka/builtins/env.c\
	  func_anezka/builtins/export.c\
	  func_anezka/builtins/unset.c\
	  func_anezka/main/command_find.c\
	  func_anezka/main/libft_utils.c\
	  func_anezka/nonbuiltins/nonbuiltins.c\
	  main.c\


OBJ = $(SRC:.c=.o)
CC = cc
#FLAGS = -Wall -Wextra -Werror
LIBS = -pthread -lreadline 

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
