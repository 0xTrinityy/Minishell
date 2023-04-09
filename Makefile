# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 10:06:19 by tbelleng          #+#    #+#              #
#    Updated: 2023/04/09 15:21:32 by luciefer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = ./src

BIN_DIR = ./bin/

SRC =	$(SRC_DIR)/builtin_exec.c     \
		$(SRC_DIR)/cd.c     	\
		$(SRC_DIR)/echo.c		\
		$(SRC_DIR)/env.c		\
		$(SRC_DIR)/exit.c		\
		$(SRC_DIR)/export.c		\
		$(SRC_DIR)/pwd.c		\
		$(SRC_DIR)/unset.c		\
		$(SRC_DIR)/main.c		\

OBJ = $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)%.o)


LIB_PATH = ./libft

LIB = -Llibft -lft

INCLUDES = ./includes

CFLAGS = -Wall -Werror -Wextra -I$(INCLUDES) -g3

all :	$(BIN_DIR) $(NAME)

$(OBJ) :	 $(BIN_DIR)%.o: $(SRC_DIR)/%.c
		@ $(CC) -I$(INCLUDES) -c $< -o $@

$(NAME) :	$(BIN_DIR) $(OBJ)
			@ $(MAKE) -s -C $(LIB_PATH)
			@ $(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)
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
