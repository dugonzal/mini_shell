# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciclo <ciclo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 09:40:27 by ciclo             #+#    #+#              #
#    Updated: 2023/03/10 20:22:28 by ciclo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src/

OBJ_DIR = obj/

INC_DIR = include

SRC_FILES := minishell

SRC := $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ := $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all: $(NAME) $(OBJ)

$(NAME): $(OBJ)
	make -C libft
	mkdir -p bin && mv libft/libft.a bin
	$(CC) $(CFLAGS) $(SRC) -o $@

#%.o -> dir obj -> src_dir %.c | objdir


$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

$(OBJ_DIR):
	mkdir -p $(OBJ)

clean:
	make -C libft clean
	rm -rf $(NAME)

fclean: clean
	rm -rf $(OBJ_DIR)

re: clean all
