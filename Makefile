# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 10:06:19 by tbelleng          #+#    #+#              #
#    Updated: 2023/05/23 18:19:54 by tbelleng         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC_DIR = ./src

BIN_DIR = ./bin/


SRC = $(SRC_DIR)/main.c			\
		$(SRC_DIR)/parsing.c		\
		$(SRC_DIR)/pars.c			\
		$(SRC_DIR)/token.c			\
		$(SRC_DIR)/token_give_cmd.c			\
		$(SRC_DIR)/syntax.c			\
		$(SRC_DIR)/syntax_replace_dollar.c	\
		$(SRC_DIR)/syntax_replace_dollar2.c	\
		$(SRC_DIR)/syntax_utils2.c	\
		$(SRC_DIR)/syntax_utils3.c	\
		$(SRC_DIR)/parsing_utils.c	\
		$(SRC_DIR)/signal.c			\
		$(SRC_DIR)/free.c			\
		$(SRC_DIR)/gnl.c			\
		$(SRC_DIR)/is_cmd.c			\
		$(SRC_DIR)/multi_cmd.c		\
		$(SRC_DIR)/error.c			\
		$(SRC_DIR)/for_free.c		\
		$(SRC_DIR)/gnl_utils.c		\
		$(SRC_DIR)/one_cmd.c		\
		$(SRC_DIR)/trimm.c			\
		$(SRC_DIR)/here_doc.c		\
		$(SRC_DIR)/built_in_exe.c	\
		$(SRC_DIR)/ft_echo.c		\
		$(SRC_DIR)/ft_env.c		    \
		$(SRC_DIR)/ft_pwd.c		    \
		$(SRC_DIR)/ft_export.c		\
		$(SRC_DIR)/ft_unset.c		\
		$(SRC_DIR)/only_file.c		\
		$(SRC_DIR)/exec.c		\
		


OBJ = $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)%.o)


LIB_PATH = ./libft

LIB = -Llibft -lft

INCLUDES = ./includes

CFLAGS = -Wall -Wextra -I$(INCLUDES) -g3

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
