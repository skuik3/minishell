# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skuik <skuik@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 12:00:13 by skuik             #+#    #+#              #
#    Updated: 2025/07/18 23:57:51 by skuik            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = tokenizer/main.c \
      tokenizer/free.c \
	  tokenizer/parse_pipes.c \
	  tokenizer/parse_tok_loop.c \
	  tokenizer/parse_token.c \
	  tokenizer/parser_handle_token.c \
	  tokenizer/process.c \
	  tokenizer/special_cases.c \
	  tokenizer/tokenizing.c \
	  

FLAGS = -Wall -Wextra -Werror -pthread

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
