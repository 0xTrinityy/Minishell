# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 10:06:19 by tbelleng          #+#    #+#              #
#    Updated: 2023/04/14 14:15:00 by tbelleng         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC_DIR = ./src

BIN_DIR = ./bin/

SRC =	$(SRC_DIR)/builtin_exec.c     \
		$(SRC_DIR)/free_all.c	\
		$(addprefixe $(SRC_DIR),$(addprefixe /builtin,/cd.c	\
		/echo.c		\
		/env.c		\
		/exit.c		\
		/export.c		\
		/pwd.c		\
		/unset.c)		\
		$(addprefixe /parcing,/parcing.c	\
		/check2.c	\
		/check.c	\
		/check3.c
		/syntaxe.c))	\
		$(SRC_DIR)/main.c		\

OBJ = $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)%.o)


LIB_PATH = ./libft

LIB = -Llibft -lft

INCLUDES = ./includes

CFLAGS = -Wall -Werror -Wextra -I$(INCLUDES) -g3i -lreadline

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
