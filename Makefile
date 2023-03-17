# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciclo <ciclo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 09:40:27 by ciclo             #+#    #+#              #
#    Updated: 2023/03/17 12:35:21 by ciclo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

CC			:= clang -g3

CFLAGS		:= -Wall -Wextra -Werror

SRC_DIR		:= src/

OBJ_DIR		:= obj/

INC_DIR		:= include/

SRC_FILES	:= minishell signals utils

SRC			:= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			:= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

OS := $(shell uname)

#condicion para compilar en mac y linux la libreria readline

ifeq ($(OS), Darwin)
	if [ -d /usr/local/opt/readline/lib ]
		brew install readline
	readline := -I/usr/local/opt/readline/include -L/usr/local/opt/readlinelib -lreadline
else
	readline :=	-L/usr/include -lreadline
endif

$(NAME): $(OBJ) $(foo)
	@make -C libft
	@mkdir -p bin && mv libft/libft.a bin
	@$(CC) $(CFLAGS) $(OBJ) $(readline) -o $@ -L bin -lft  
	@printf	"$(BLUE)Compiling $@$(DEFAULT)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@if [ ! -d "libft" ]; then git clone https://github.com/dugonzal/libft.git;  fi
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)*
	@echo "Compiling $<"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

all: $(NAME)

clean:
	@make -C libft clean
	@rm -rf $(NAME)
	@echo "Cleaning $(NAME)"

fclean: clean
	@rm -rf $(OBJ_DIR) bin
	@make -C libft fclean
	@rm -rf $(OBJ_DIR)
	@echo "Cleaning $(OBJ_DIR) and bin"

re: fclean all
