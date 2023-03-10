# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciclo <ciclo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 09:40:27 by ciclo             #+#    #+#              #
#    Updated: 2023/03/10 21:36:01 by ciclo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src/

OBJ_DIR = obj/

INC_DIR = include/

SRC_FILES := minishell utils

SRC := $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ := $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

$(NAME): $(OBJ)
	make -C libft
	mkdir -p bin && mv libft/libft.a bin
	$(CC) $(CFLAGS) $(OBJ) -o $@ -L bin -lft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)*

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

all: $(NAME)

clean:
	make -C libft clean
	rm -rf $(NAME)

fclean: clean
	rm -rf $(OBJ_DIR) bin
	make -C libft fclean

re: fclean all
