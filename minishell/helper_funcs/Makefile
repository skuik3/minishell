# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skuik <skuik@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/12 13:28:18 by skuik             #+#    #+#              #
#    Updated: 2025/02/11 14:17:27 by skuik            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
AR = ar
CC = cc
RM = rm
COMPILER_FLAGS = -Wall -Wextra -Werror

SRC = ft_isascii.c ft_isprint.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
			ft_tolower.c ft_toupper.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
			ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
			ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_memchr.c ft_memcmp.c ft_strdup.c ft_calloc.c ft_itoa.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c \
			get_next_line.c get_next_line_utils.c 
		
OBJ = $(SRC:%.c=%.o)

%.o: %.c
	$(CC) $(COMPILER_FLAGS) -c $< -o $@

all: $(OBJ)
	$(AR) -rcs $(NAME) $(OBJ)

clean:
	$(RM) -f $(OBJ)
fclean: clean
	$(RM) -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
