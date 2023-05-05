# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luciefer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/15 11:35:37 by luciefer          #+#    #+#              #
#    Updated: 2023/05/05 11:37:32 by luciefer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = ./src

BIN_DIR = ./bin/

SRC =	$(SRC_DIR)/main.c			\
		$(SRC_DIR)/parsing.c		\
		$(SRC_DIR)/pars.c			\
		$(SRC_DIR)/token.c			\
		$(SRC_DIR)/token2.c			\
		$(SRC_DIR)/syntax.c			\
		$(SRC_DIR)/syntax_utils.c	\
		$(SRC_DIR)/syntax_utils2.c	\
		$(SRC_DIR)/syntax_utils3.c	\
		$(SRC_DIR)/parsing_utils.c	\
		$(SRC_DIR)/signal.c			\
		$(SRC_DIR)/free.c			\
		$(SRC_DIR)/exec.c			\

OBJ = $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)%.o)


LIB_PATH = ./libft

LIB = -Llibft -lft

INCLUDES = ./includes

CFLAGS = -Wall -Werror -Wextra -I$(INCLUDES) -g3

all :	$(BIN_DIR) $(NAME)

$(OBJ) :	 $(BIN_DIR)%.o: $(SRC_DIR)/%.c
		@ $(CC) $(CFLAGS) -c $< -o $@

$(NAME) :	$(BIN_DIR) $(OBJ)
			@ $(MAKE) -s -C $(LIB_PATH)
			@ $(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) -lreadline
			@ echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mDone ! ✅"

$(BIN_DIR) :
		@ mkdir -p $(BIN_DIR)

clean :
		@ $(MAKE) -s clean -C $(LIB_PATH)
		@ rm -f $(OBJ)
		@ rm -rf $(BIN_DIR)
		@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove binary files .. 🧹"

fclean : clean
		@ $(MAKE) -s fclean -C $(LIB_PATH)
		@ rm -f $(NAME)
		@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove executable .. 🗑️"
		
re :
	@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRecompile .. 🔄"
	@ $(MAKE) -s fclean all

.PHONY: all clean fclean re
