/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:15:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/09/01 12:05:38 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include <termios.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <termcap.h>

# if __linux__
#  include <sys/wait.h>
# endif

# define PROMPT "$> "

# define BUF_SIZE 16
# define HISTORY_SIZE 50

# define RETURN_NO_ACCESS 126
# define RETURN_COMMAND_NOT_FOUND 127

/* Keys */

# define ARROW_UP "\x1B[A"
# define ARROW_DOWN "\x1B[B"
# define ARROW_LEFT "\x1B[D"
# define ARROW_RIGHT "\x1B[C"
# define RETURN_KEY "\x0A"
# define BACKSPACE "\x7F"

/* Key sequences */

# define CTRL_W "\x17"

/* Errors */

# define ERR_ENV_MISSING_TERM "No TERM environment variable set."
# define ERR_TERMCAP_NO_ACCESS "Unable to access termcap database."
# define ERR_TERMCAP_NO_ENTRY "No database entry for current terminal type."
# define ERR_LINE_READ "input read error"
# define ERR_HISTORY_RECALL "history recall error"
# define ERR_CHILD_PROC_FAIL "cannot make child process"
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

/* Globals */

extern int	g_last_signal;

/* Types */

typedef struct s_state
{
	char *const		*env;
	char			*input;
	size_t			prev_input_len;
	int				continue_previous_node;
	int				in_double_quotes;
	int				in_assignment;
	int				has_seen_tilde_in_word;
	size_t			cursor;
	size_t			input_start_x;
	size_t			input_start_y;
	struct termios	input_conf;
	struct termios	orig_conf;
	char			*history[HISTORY_SIZE];
	int				history_index;
	int				last_return_value;
	int				exit_return_value;
	int				exiting;
}	t_state;

typedef enum e_token_type
{
	TOKEN_LITERAL,
	TOKEN_WHITESPACE,
	TOKEN_DOLLAR,
	TOKEN_TILDE,
	TOKEN_DOUBLEQUOTE,
	TOKEN_CURLY_OPEN,
	TOKEN_CURLY_CLOSED,
	TOKEN_PLUS,
	TOKEN_MINUS
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef int	t_input_handler(char buf[16], t_state *state);

typedef struct s_input_handler_dispatch
{
	char			*activator;
	t_input_handler	*run;
}	t_input_handler_dispatch;

typedef int	t_cmd(char *const *args, t_state *state);

typedef struct s_cmd_dispatch
{
	const char	*name;
	t_cmd		*run;
}	t_cmd_dispatch;

typedef int	t_parse_function(t_token **cursor, t_state *state, char ***result);

typedef struct s_cmd_env
{
	int		exclusive;
	char	**args;
	char	**env;
}	t_cmd_env;

/* Files */

/* signal.c */
void	check_signal(t_state *state);
void	set_signal_handling(void);

/* shlvl.c */
int		set_shlvl(char *const **env);

/* input.c */
int		get_input(t_state *state);

/* input_configuration.c */
int		configure_input(t_state *state);
int		set_input_config(t_state *state);
int		set_orig_config(t_state *state);

/* input_handlers.c */
int		handle_char(char buf[BUF_SIZE], int *index, t_state *state);

/* cursor.c */
void	save_cursor(void);
int		parse_cursor(char buf[BUF_SIZE], t_state *state);
void	load_cursor(t_state *state);

/* history.c */
int		history_store(char *input, t_state *state);
int		history_recall(int diff, t_state *state);

/* autocomplete.c */
void	autocomplete(t_state *state);

/* literals.c */
int		check_literals(t_token **cursor, t_state *state, char ***result);

/* escapes.c */
int		check_escape_sequence(char buf[BUF_SIZE], t_state *state);

/* lexer.c */
t_token	*tokenize(char *line);

/* parser.c */
char	**parse(t_token *list, t_state *state);
int		expect_token(t_token **cursor, t_token_type type, t_token *on_fail);
int		add_to_result(char ***result, char *value, t_state *state);

/* expansions.c */
int		expand_tilde(t_token **cursor, t_state *state, char ***result);
int		expand_variable(t_token **cursor, t_state *state, char ***result);

/* token.c */
t_token	*token_add(t_token **list, t_token_type type, char *value);
void	token_free(t_token **token);
int		token_is_word_end(t_token *token);

/* token_list.c */
void	token_list_free(t_token **list);

/* environment.c */
int		env_set(const char *name, const char *value, char *const **env);
int		env_unset(const char *name, char *const **env);
void	env_print_all(char *const *env);
size_t	valid_env_name_length(char *name);

/* environment_getters.c */
char	*env_get(const char *name, char *const *env);
char	*env_get_or(char *name, char *on_fail, char *const *env);
char	**env_get_pointer(const char *name, char *const *env);

/* bin.c */
int		bin_env_find(const char *name, char *const *env, char **result);
int		bin_execute(char *path, char **args, char *const *env, int underscore);

/* built_ins.c */
t_cmd	*get_built_in(const char *name);
char	*search_for_built_in(const char *partial_name);
int		run_built_in(t_cmd cmd, char *const *args, t_state *state);

/* executor.c */
int		execute(char *const *args, t_state *state);

/* return_value.c */
int		get_return_value_from_status(int status);
void	set_return_value(int return_value, t_state *state);

/* Built-in commands */

/* cmd_echo.c */
int		cmd_echo(char *const *args, t_state *state);

/* cmd_cd.c */
int		cmd_cd(char *const *args, t_state *state);

/* cmd_env.c */
int		cmd_env(char *const *args, t_state *state);

/* cmd_setenv.c */
int		cmd_setenv(char *const *args, t_state *state);

/* cmd_unsetenv.c */
int		cmd_unsetenv(char *const *args, t_state *state);

/* cmd_exit.c */
int		cmd_exit(char *const *args, t_state *state);

/* Utilities */

/* utils.c */
void	clear_input(t_state *state, int newline);
void	print_state(t_state *state, int newline);
void	*var_copy(void *var);

/* error.c */
int		print_error(char *message, int return_value);
int		print_named_error(char *name, char *message, int return_value);

#endif
