# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dugonzal <dugonzal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 09:40:27 by ciclo             #+#    #+#              #
#    Updated: 2023/06/14 15:37:57 by dugonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= clang -g3
CFLAGS		:= -Wall -Wextra -Werror
SRC_DIR		:= src/
OBJ_DIR		:= obj/
INC_DIR		:= include/
SHELL 		:= /bin/bash

# folders for sources
parser_dir 	:= parser/
parser		:= split_token split_token_utils parser parser_utils parser_utils_2 lexer lexer_utils utils

builtins_dir 	:= builtins/
builtins		:= builtins exit echo pwd env export export_utils unset cd getenv

SRC_FILES 	+= $(addprefix $(parser_dir),$(parser))
SRC_FILES 	+= $(addprefix $(builtins_dir),$(builtins))

SRC_FILES	+=	minishell  utils signals exec exec_utils expanser expanser_utils  redirect redirect_utils

SRC			:= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			:= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

DEFAULT	= \033[0;39m
GRAY 	= \033[0;90m
RED 	= \033[0;91m
GREEN 	= \033[0;92m
YELLOW 	= \033[0;93m
BLUE 	= \033[0;94m
MAGENTA = \033[0;95m
CYAN 	= \033[0;96m
WHITE 	= \033[0;97m

OS := $(shell uname)

ifeq ($(OS), Darwin)
	#probar que si funcione en Darwin xd
	readline := -I/goinfre/$(USER)/$(USER)/.brew/opt/readline  -L/goinfre/$(USER)/$(USER)/.brew/opt/readline/lib -lreadline
else
	readline :=	-lreadline
endif

ifndef verbose
.SILENT:
endif

$(NAME): $(OBJ)
	make -C libft && mkdir -p bin && mv libft/libft.a bin
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L bin -lft $(readline)
	printf "$(BLUE) 🚀 $@ $(DEFAULT)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)$(parser_dir)
	mkdir -p $(OBJ_DIR)$(builtins_dir)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)* -I libft -I/goinfre/$(USER)/$(USER)/.brew/opt/readline/include
	printf  "$(GREEN) 🚀  $< $(DEFAULT)\n"

all: $(NAME)

clean:
	make -C libft clean
	rm -rf $(NAME)
	printf "$(YELLOW) Cleaning $(NAME) $(DEFAULT)\n"

fclean: clean
	rm -rf bin  $(OBJ_DIR)
	make -C libft fclean
	printf "$(BLUE)Cleaning $(OBJ_DIR) and bin \n$(DEFAULT)"

val: $(NAME)
	valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all --log-file=valgrind.log  cat  < command | ./minishell; cat valgrind.log

re: fclean all val
