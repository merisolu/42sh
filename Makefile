# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 13:02:44 by jumanner          #+#    #+#              #
#    Updated: 2022/10/27 11:28:25 by jumanner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = gcc

INCLUDE_DIR = ./include

LIB_DIR = ./libft
LIB_INCLUDE_DIR = ./libft/include
LIB_PATH = ./libft/libft.a

SRC_DIR = ./src

AST_DIR = ast
AST_FILES = ast_add_args.c ast_pipe_sequence.c ast_free.c \
				ast_redir_recursion.c ast_retokenize.c ast_parse_expansions.c \
				ast_cleanse_ws.c grammar.c

BUILT_IN_DIR = built-in
BUILT_IN_FILES = built_ins.c cmd_cd.c cmd_echo.c cmd_env.c cmd_setenv.c \
				cmd_unsetenv.c cmd_exit.c

DEBUG_DIR = debug
DEBUG_FILES = ast_print_debug.c print_tokens.c

ENVIRONMENT_DIR = environment
ENVIRONMENT_FILES = environment.c environment_getters.c shlvl.c

EXECUTION_DIR = execution
EXECUTION_FILES = bin.c executor.c fork.c pipes.c redirects.c \
					tokenize_and_execute.c

EXPANSION_DIR = expansion
EXPANSION_FILES = expand_tilde.c expand_variables.c

INPUT_DIR = input
INPUT_FILES = autocomplete.c clipboard.c ctrl_d.c cursor.c cursor_utils.c \
				history.c input.c input_configuration.c input_handlers.c \
				input_utils.c movement.c movement_alt.c

PARSER_DIR = parser
PARSER_FILES = eat_read_token.c get_token_type.c lexer.c literals.c parser.c \
				token.c token_list.c

SIGNAL_DIR = signal
SIGNAL_FILES = signal.c

UTIL_DIR = util
UTIL_FILES = error.c utils.c return_value.c

SRC_FILES = main.c \
			$(patsubst %, $(AST_DIR)/%, $(AST_FILES)) \
			$(patsubst %, $(BUILT_IN_DIR)/%, $(BUILT_IN_FILES)) \
			$(patsubst %, $(DEBUG_DIR)/%, $(DEBUG_FILES)) \
			$(patsubst %, $(ENVIRONMENT_DIR)/%, $(ENVIRONMENT_FILES)) \
			$(patsubst %, $(EXECUTION_DIR)/%, $(EXECUTION_FILES)) \
			$(patsubst %, $(EXPANSION_DIR)/%, $(EXPANSION_FILES)) \
			$(patsubst %, $(INPUT_DIR)/%, $(INPUT_FILES)) \
			$(patsubst %, $(PARSER_DIR)/%, $(PARSER_FILES)) \
			$(patsubst %, $(SIGNAL_DIR)/%, $(SIGNAL_FILES)) \
			$(patsubst %, $(UTIL_DIR)/%, $(UTIL_FILES)) \

SRCS := $(patsubst %, $(SRC_DIR)/%, $(SRC_FILES))

OBJ_DIR = ./obj
OBJS := $(patsubst %, $(OBJ_DIR)/%, $(SRC_FILES:.c=.o))

GCC_FLAGS = -g -Wall -Wextra -Werror

$(NAME): $(LIB_PATH) $(OBJS)
	$(CC) $(GCC_FLAGS) $(OBJS) -o $(NAME) -ltermcap -L $(LIB_DIR) -lft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(GCC_FLAGS) -I $(INCLUDE_DIR) -I $(LIB_INCLUDE_DIR) -c $< -o $@

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
