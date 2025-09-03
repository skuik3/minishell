# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skuik <skuik@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 12:00:13 by skuik             #+#    #+#              #
#    Updated: 2025/09/03 16:41:03 by skuik            ###   ########.fr        #
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
	  main.c\
	  
OBJS = tokenizing.o main.o process.o parse_token.o
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
