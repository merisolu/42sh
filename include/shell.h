/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:15:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/26 14:16:03 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include <termios.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <termcap.h>

//only needed in redirects.c maybe put this in a separate header file
#include <fcntl.h>

//only needed in expand_tildes.c for finding usernames, see above comment
#include <pwd.h>

# if __linux__
#  include <sys/wait.h>
# endif

# define PIPE_READ 0
# define PIPE_WRITE 1

# define PROMPT "$> "
# define MULTILINE_PROMPT "> "

# define REDIR_APPEND ">>"
# define REDIR_HEREDOC "<<"

# define BUF_SIZE 16
# define INPUT_MAX_SIZE LINE_MAX
# define HISTORY_SIZE 50

# define RETURN_NO_ACCESS 126
# define RETURN_COMMAND_NOT_FOUND 127

# define RETURN_CTRL_D 127

# define TRUE 1
# define FALSE 0

# define CC_SUSPEND VDSUSP

# if __linux__
#  undef CC_SUSPEND
#  define CC_SUSPEND VSUSP
# endif

/* Keys */

# define ARROW_UP "\x1B[A"
# define ARROW_DOWN "\x1B[B"
# define ARROW_LEFT "\x1B[D"
# define ARROW_RIGHT "\x1B[C"
# define ARROW_UP_ALT "\x1B[1;3A"
# define ARROW_DOWN_ALT "\x1B[1;3B"
# define ARROW_LEFT_ALT "\033b"
# define ARROW_RIGHT_ALT "\033f"
# define RETURN_KEY "\x0A"
# define BACKSPACE "\x7F"
# define HOME_KEY "\x1B[H"
# define END_KEY "\x1B[F"
# define TAB "\t"

/* Key sequences */

# define CTRL_D "\x04"
# define CTRL_K "\x0b"
# define CTRL_U "\x15"
# define CTRL_W "\x17"
# define CTRL_Y "\x19"

/* Errors */

# define ERR_ENV_MISSING_TERM "No TERM environment variable set."
# define ERR_TERMCAP_NO_ACCESS "Unable to access termcap database."
# define ERR_TERMCAP_NO_ENTRY "No database entry for current terminal type."
# define ERR_LINE_READ "input read error"
# define ERR_HISTORY_RECALL "history recall error"
# define ERR_CHILD_PROC_FAIL "cannot make child process"
# define ERR_CHILD_PIPE_FAIL "cannot make child pipes"
# define ERR_PIPE_FAIL "failed to create pipe"
# define ERR_DUP_FAIL "failed to duplicate file descriptor"
# define ERR_COM_NOT_FOUND "command not found"
# define ERR_NO_PERMISSION "Permission denied"
# define ERR_TOO_FEW_ARGS "too few arguments"
# define ERR_TOO_MANY_ARGS "too many arguments"
# define ERR_NO_SUCH_FILE_OR_DIR "No such file or directory"
# define ERR_IS_DIR "is a directory"
# define ERR_IS_NOT_DIR "Not a directory"
# define ERR_CANNOT_GET_CWD "error retrieving current directory"
# define ERR_INVALID_PATH "path is invalid"
# define ERR_MALLOC_FAIL "memory allocation failed"
# define ERR_TERMIOS_FAIL "failed to set terminal attributes"
# define ERR_SIZE_GET_FAIL "failed to read terminal size"
# define ERR_NO_HOME "HOME not set"
# define ERR_NO_OLDPWD "OLDPWD not set"
# define ERR_SYNTAX "syntax error, unexpected token"

/* Globals */

extern int				g_last_signal;

/* Types */

typedef struct s_state
{
	char *const		*env;
	char			*input;
	char			*clipboard;
	int				continue_previous_node;
	int				in_double_quotes;
	int				in_assignment;
	int				has_seen_tilde_in_word;
	size_t			cursor;
	size_t			input_start_x;
	size_t			input_start_y;
	size_t			width;
	size_t			height;
	struct termios	input_conf;
	struct termios	orig_conf;
	char			*history[HISTORY_SIZE];
	int				history_index;
	int				last_return_value;
	int				exit_return_value;
	int				exiting;
}	t_state;

typedef enum e_input_result
{
	INPUT_NOTHING_READ = -2,
	INPUT_READ_ERROR = -1,
	INPUT_NO_NEWLINE_FOUND = 0,
	INPUT_NEWLINE_FOUND = 1
}	t_input_result;

typedef enum e_token_type
{
	TOKEN_WORD = 1 << 0,
	TOKEN_WHITESPACE = 1 << 1,
	TOKEN_DOLLAR = 1 << 2,
	TOKEN_TILDE = 1 << 3,
	TOKEN_DOUBLE_QUOTE = 1 << 4,
	TOKEN_SINGLE_QUOTE = 1 << 5,
	TOKEN_CURLY_OPEN = 1 << 6,
	TOKEN_CURLY_CLOSED = 1 << 7,
	TOKEN_PLUS = 1 << 8,
	TOKEN_MINUS = 1 << 9,
	TOKEN_PIPE = 1 << 10,
	TOKEN_SEMICOLON = 1 << 11,
	TOKEN_COLON = 1 << 12,
	TOKEN_GT = 1 << 13,
	TOKEN_LT = 1 << 14,
	TOKEN_DGT = 1 << 15,
	TOKEN_DLT = 1 << 16,
	TOKEN_LTAND = 1 << 17,
	TOKEN_GTAND = 1 << 18,
	TOKEN_AMPERSAND = 1 << 19,
	TOKEN_BACKSLASH = 1 << 20,
	TOKEN_FWD_SLASH = 1 << 21,
	TOKEN_NEWLINE = 1 << 22,
	TOKEN_EQUALS = 1 << 24,
	TOKEN_NULL = 1 << 25
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_token_dispatch
{
	char				symbol;
	t_token_type		token;
}	t_token_dispatch;

typedef struct s_tokenizer
{
	int		in_quotes;
	char	quote_type;
	char	*buff;
	size_t	buff_idx;
}	t_tokenizer;

typedef t_input_result	t_key_handler(t_state *state);

typedef struct s_key_handler_dispatch
{
	char			*activator;
	t_key_handler	*run;
}	t_key_handler_dispatch;

typedef int				t_movement_handler(char buf[16], t_state *state);

typedef struct s_movement_handler_dispatch
{
	char				*activator;
	t_movement_handler	*run;
}	t_movement_handler_dispatch;

typedef int				t_cmd(char *const *args, t_state *state);

typedef struct s_cmd_dispatch
{
	const char	*name;
	t_cmd		*run;
}	t_cmd_dispatch;

typedef int				t_parse_function(\
	t_token **cursor, t_state *state, char **result);

typedef struct s_cmd_env
{
	int		exclusive;
	char	**args;
	char	**env;
}	t_cmd_env;

typedef enum e_ast_node_type
{
	AST_PIPE_SEQUENCE,
	AST_SIMPLE_COMMAND,
	AST_COMMAND_ARGS,
	AST_REDIRECTIONS
}	t_ast_node_type;

typedef struct s_ast
{
	t_ast_node_type	node_type;
	char			**arg_list;
	char			*in_file;
	char			*out_file;
	char			*in_type;
	char			*out_type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_redir
{
	int	fd_out;
	int	fd_in;
	int	saved_out;
	int	saved_in;
}	t_redir;

typedef struct s_pipes
{
	int	read[2];
	int	write[2];
}	t_pipes;

typedef struct s_ast_execution
{
	t_ast	*node;
	t_redir	*redirect;
	t_pipes	*pipes;
	int		is_at_end;
}	t_ast_execution;

/* DEBUG FUNCTION - DELETE ME */
/* ast_print_debug.c */
void			print_ast(t_ast **tree);

/* DEBUG FUNCTION - DELETE ME */
/* print_tokens.c */
void	print_tokens(t_token *result);

/* Files */

/* ast_add_args.c */
char			**ast_add_args(t_token **cursor);

/* ast_free.c */
void			ast_free(t_ast **tree_list);

/* ast_parse_expansions.c */
int				ast_parse_expansions(t_ast *root, t_state *state);

/* ast_pipe_sequence.c */
t_ast			*ast_pipe_sequence(t_token **cursor);

/* ast_redirect_recursion.c */
int				ast_redirect_recursion(t_ast *node, t_token **cursor);

/* ast_retokenize.c */
t_token			*ast_retokenize(char *line);

/* grammar.c */
t_ast			**construct_ast_list(t_token **cursor);

/* redirects.c */
void			initialize_redir_struct(t_redir *r);
int				reset_io(t_redir r);
int				handle_redirects(t_ast *redir_node, t_redir *r);

/* pipes.c */
void			pipe_reset(int pipe[2]);
void			pipe_close(int pipe[2]);
void			pipes_reset(int pipe1[2], int pipe2[2]);
int				pipes_connect(int read_pipe[2], int write_pipe[2]);
void			pipes_copy(int target[2], int source[2]);

/* signal.c */
void			check_signal(t_state *state);
void			set_signal_handling(void);

/* shlvl.c */
int				set_shlvl(char *const **env);

/* input.c */
t_input_result	get_input(t_state *state);

/* input_configuration.c */
int				configure_input(t_state *state);
int				set_input_config(t_state *state);
int				set_orig_config(t_state *state);

/* input_handlers.c */
t_input_result	handle_key(char *buf, t_state *state);

/* input_utils.c */
size_t			input_get_row_count(t_state *state, size_t index);
void			input_get_line_properties(\
	t_state *state, size_t index, size_t *start, size_t *length);

/* cursor.c */
void			save_cursor(t_state *state);
void			load_cursor(t_state *state);

/* cursor_utils.c */
void			move_cursor_to_saved_position(t_state *state);
size_t			cursor_get_column(t_state *state, size_t index);
size_t			cursor_get_row(t_state *state, size_t index);

/* history.c */
int				history_store(char *input, t_state *state);
int				history_recall(int diff, t_state *state);

/* autocomplete.c */
int				autocomplete(t_state *state);

/* clipboard.c */
t_input_result	cut_word(t_state *state);
t_input_result	cut_to_cursor(t_state *state);
t_input_result	cut_from_cursor(t_state *state);
t_input_result	paste(t_state *state);

/* ctrl_d.c */
int				ctrl_d(t_state *state);

/* literals.c */
int				check_literals(\
	t_token **cursor, t_state *state, char **result);

/* movement.c */
int				check_movement(char *buf, t_state *state);

/* movement_alt.c */
int				handle_alt_left_right(char buf[BUF_SIZE], t_state *state);
int				handle_alt_up(char buf[BUF_SIZE], t_state *state);
int				handle_alt_down(char buf[BUF_SIZE], t_state *state);

/* tokenize_and_execute.c */
void			tokenize_and_execute(t_state *state);

/* lexer.c */
t_token			*tokenize(char *line);

/* get_token_type.c */
t_token_type	get_token_type(char value, int in_quotes);

/* parser.c */
t_ast			**parse(t_token *list, t_state *state);
int				add_to_result(char **result, char *value, t_state *state);
void			reset_state(t_state *state);

/* eat_read_token.c */
int				eat_token(\
	t_token **cursor, t_token_type type, t_token *on_fail);
int				read_token(\
	t_token **cursor, t_token_type type, t_token *on_fail);

/* expand_tilde.c */
int				expand_tilde(t_token **cursor, t_state *state, char **result);

/* expand_variables.c */
int				expand_variable(\
	t_token **cursor, t_state *state, char **result);

/* token.c */
t_token			*token_add(t_token **list, t_token_type type, char *value);
void			token_free(t_token **token);
int				token_is_word_end(t_token *token);

/* token_list.c */
void			token_list_free(t_token **list);

/* environment.c */
int				env_set(const char *name, const char *value, char *const **env);
int				env_unset(const char *name, char *const **env);
void			env_print_all(char *const *env);
size_t			valid_env_name_length(char *name);

/* environment_getters.c */
char			*env_get(const char *name, char *const *env);
char			*env_get_or(char *name, char *on_fail, char *const *env);
char			**env_get_pointer(const char *name, char *const *env);

/* bin.c */
int				bin_env_find(const char *name, char *const *env, char **result);
pid_t			bin_execute(char *path, char **args, char *const *env, t_pipes *pipes);

/* built_ins.c */
t_cmd			*get_built_in(const char *name);
char			*search_for_built_in(const char *partial_name);
pid_t			run_built_in(t_cmd cmd, char *const *args, t_state *state, t_pipes *pipes);

/* executor.c */
pid_t			execute(char *const *args, t_state *state, t_pipes *pipes);

/* fork.c */
pid_t			start_fork(t_pipes *pipes);

/* return_value.c */
int				get_return_value_from_status(int status);
void			set_return_value(int return_value, t_state *state);

/* Built-in commands */

/* cmd_echo.c */
int				cmd_echo(char *const *args, t_state *state);

/* cmd_cd.c */
int				cmd_cd(char *const *args, t_state *state);

/* cmd_env.c */
int				cmd_env(char *const *args, t_state *state);

/* cmd_setenv.c */
int				cmd_setenv(char *const *args, t_state *state);

/* cmd_unsetenv.c */
int				cmd_unsetenv(char *const *args, t_state *state);

/* cmd_exit.c */
int				cmd_exit(char *const *args, t_state *state);

/* Utilities */

/* utils.c */
void			update_window_size(t_state *state);
void			clear_input(t_state *state, int newline);
void			print_state(t_state *state);
void			*var_copy(void *var);

/* error.c */
int				print_error(char *message, int return_value);
int				print_named_error(char *name, char *message, int return_value);

#endif
