# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 13:02:44 by jumanner          #+#    #+#              #
#    Updated: 2023/01/26 13:42:23 by jumanner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

CC = gcc

INCLUDE_DIR = ./include

LIB_DIR = ./libft
LIB_INCLUDE_DIR = ./libft/include
LIB_PATH = ./libft/libft.a

SRC_DIR = ./src

AST_DIR = ast
AST_FILES = ast_add_args.c ast_pipe_sequence.c ast_redir_control.c \
				ast_retokenize.c ast_free.c	ast_fd_agg_format_check.c \
				construct_ast_list.c ast_simple_command.c \
				ast_add_fd_aggregation.c ast_is_separator.c ast_end.c \
				check_redir_syntax.c ast_add_redir_struct.c \
				check_redir_tokens.c check_var_syntax.c \
				ast_to_string.c ast_to_string_utils.c

AUTOCOMPLETE_DIR = autocomplete
AUTOCOMPLETE_FILES = autocomplete.c search_commands.c directory_search.c \
					filter_matching.c truncate_result.c \
					check_result_is_dir.c search_file_paths.c \
					search_variables.c wrap_up.c search_env_intern.c \
					find_query.c search_exec.c directory_search_loops.c\
					autocomplete_display_control.c find_longest.c \
					autocomplete_display_columns.c \
					autocomplete_position_cursor.c

BUILT_INS_DIR = built-ins
BUILT_INS_FILES = built_ins.c built_ins_flags.c cmd_cd.c cmd_echo.c \
				cmd_fc.c cmd_fc_editor.c cmd_fc_range.c \
				cmd_exit.c cmd_execute_script.c cmd_true_false.c \
				cmd_type.c cmd_set.c cmd_export.c cmd_unset.c delete_var.c \
				export_set.c print_exported.c cmd_hash.c check_path_change.c \
				cmd_jobs.c cmd_fg.c cmd_bg.c fg_bg_utils.c

CLEANUP_DIR = cleanup
CLEANUP_FILES = cleanup.c

CURSOR_DIR = cursor
CURSOR_FILES = cursor.c cursor_utils.c

DEBUG_DIR = debug
DEBUG_FILES = ast_print_debug.c check_print_ast.c

DISPLAY_DIR = display
DISPLAY_FILES = display.c

ENVIRONMENT_DIR = environment
ENVIRONMENT_FILES = environment.c environment_getters.c shlvl.c

EXECUTION_DIR = execution
EXECUTION_FILES = bin.c executor.c executor_path_utils.c fork.c pids.c pipes.c \
					heredocs.c reset_io.c redirects.c tokenize_and_execute.c \
					execute_fd_aggregation.c handle_logical_ops.c \
					copy_orig_fd.c execute_redirection.c \
					set_internal_variables.c execute_simple_command.c \
					remove_temp_vars.c update_env_execution.c \
					jobs.c jobs_print.c jobs_find.c jobs_utils.c \
					process_group.c

EXPANSION_DIR = expansion
EXPANSION_FILES = expand_tilde.c expand_variables.c expand_node.c \
				  	parse_expansions.c

HASH_DIR = hash
HASH_FILES = hash_table.c hash_table_getters.c fnv1.c

HISTORY_DIR = history
HISTORY_FILES = history.c history_save.c history_load.c history_utils.c

INPUT_DIR = input
INPUT_FILES = clipboard_copy.c clipboard_cut.c clipboard_paste.c \
				clipboard_utils.c ctrl_d.c \
				input.c input_handlers.c input_context.c input_utils.c \
				movement.c movement_alt_horizontal.c movement_alt_vertical.c

PARSING_DIR = parsing
PARSING_FILES = eat_read_token.c get_token_type.c lexer.c literals.c \
				token.c token_list.c add_to_result.c check_quotes.c

SETUP_DIR = setup
SETUP_FILES = setup.c setup_termcaps.c setup_input.c setup_fd.c

SIGNALS_DIR = signals
SIGNALS_FILES = signal.c signal_handlers.c

TERMINAL_DIR = terminal
TERMINAL_FILES = terminal_configuration.c

UTILS_DIR = utils
UTILS_FILES = error.c utils.c utils_input.c return_value.c syntax_error.c \
			  fd_is_open.c

SRC_FILES = main.c \
			$(patsubst %, $(AST_DIR)/%, $(AST_FILES)) \
			$(patsubst %, $(AUTOCOMPLETE_DIR)/%, $(AUTOCOMPLETE_FILES)) \
			$(patsubst %, $(BUILT_INS_DIR)/%, $(BUILT_INS_FILES)) \
			$(patsubst %, $(CLEANUP_DIR)/%, $(CLEANUP_FILES)) \
			$(patsubst %, $(CURSOR_DIR)/%, $(CURSOR_FILES)) \
			$(patsubst %, $(DEBUG_DIR)/%, $(DEBUG_FILES)) \
			$(patsubst %, $(DISPLAY_DIR)/%, $(DISPLAY_FILES)) \
			$(patsubst %, $(ENVIRONMENT_DIR)/%, $(ENVIRONMENT_FILES)) \
			$(patsubst %, $(EXECUTION_DIR)/%, $(EXECUTION_FILES)) \
			$(patsubst %, $(EXPANSION_DIR)/%, $(EXPANSION_FILES)) \
			$(patsubst %, $(HASH_DIR)/%, $(HASH_FILES)) \
			$(patsubst %, $(HISTORY_DIR)/%, $(HISTORY_FILES)) \
			$(patsubst %, $(INPUT_DIR)/%, $(INPUT_FILES)) \
			$(patsubst %, $(PARSING_DIR)/%, $(PARSING_FILES)) \
			$(patsubst %, $(SETUP_DIR)/%, $(SETUP_FILES)) \
			$(patsubst %, $(SIGNALS_DIR)/%, $(SIGNALS_FILES)) \
			$(patsubst %, $(TERMINAL_DIR)/%, $(TERMINAL_FILES)) \
			$(patsubst %, $(UTILS_DIR)/%, $(UTILS_FILES))

SRCS := $(patsubst %, $(SRC_DIR)/%, $(SRC_FILES))

OBJ_DIR = ./obj
OBJS := $(patsubst %, $(OBJ_DIR)/%, $(SRC_FILES:.c=.o))

GCC_FLAGS = -Wall -Wextra -Werror -g

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
