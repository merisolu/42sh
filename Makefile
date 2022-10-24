# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 13:02:44 by jumanner          #+#    #+#              #
#    Updated: 2022/10/24 19:29:35 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = gcc

INCLUDE_DIR = ./include

LIB_DIR = ./libft
LIB_INCLUDE_DIR = ./libft/include
LIB_PATH = ./libft/libft.a

SRC_FILES = main.c \
			signal.c \
			shlvl.c \
			input.c input_configuration.c input_handlers.c input_utils.c \
			cursor.c cursor_utils.c \
			history.c autocomplete.c clipboard.c ctrl_d.c \
			movement.c movement_alt.c \
			literals.c \
			lexer.c parser.c expand_tilde.c expand_variables.c \
			grammar.c ast_add_args.c ast_pipe_sequence.c ast_free.c \
			ast_redir_recursion.c ast_retokenize.c ast_parse_expansions.c \
			token.c token_list.c get_token_type.c \
			environment.c environment_getters.c \
			redirects.c \
			bin.c executor.c return_value.c tokenize_and_execute.c \
			built_ins.c cmd_cd.c cmd_echo.c cmd_env.c cmd_setenv.c \
			cmd_unsetenv.c cmd_exit.c \
			utils.c error.c \
			ast_print_debug.c print_tokens.c # DELETE ME
SRC_DIR = ./src
SRCS := $(patsubst %, $(SRC_DIR)/%, $(SRC_FILES))

OBJ_DIR = ./obj
OBJS := $(patsubst %, $(OBJ_DIR)/%, $(SRC_FILES:.c=.o))

GCC_FLAGS = -O2 -Wall -Wextra -Werror

$(NAME): $(LIB_PATH) $(OBJS)
	$(CC) $(GCC_FLAGS) $(OBJS) -o $(NAME) -ltermcap -L $(LIB_DIR) -lft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(GCC_FLAGS) -I $(INCLUDE_DIR) -I $(LIB_INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: all clean fclean re run

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(LIB_PATH):
	make -C $(LIB_DIR)

run: $(NAME)
	./$(NAME)
