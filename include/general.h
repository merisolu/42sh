/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:42:24 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/13 13:03:06 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

/* Includes */

# include <stdlib.h>
# include <termios.h>
# include <stdbool.h>

/* Constants */

# define HISTORY_SIZE 50

# define PIPE_READ 0
# define PIPE_WRITE 1

# define BUF_SIZE 16
# define INPUT_MAX_SIZE LINE_MAX

# define PROMPT "$> "
# define MULTILINE_PROMPT "> "
# define REDIR_OUT ">"
# define REDIR_APPEND ">>"
# define REDIR_IN "<"
# define REDIR_HEREDOC "<<"
# define FD_AGG_IN "<&"
# define FD_AGG_OUT ">&"

/* Types */

# define MAX_PIDS 709
# define MAX_JOBS MAX_PIDS

# define MAGIC_NUMBER "#!42\n"

/* Return values */

# define RETURN_NO_ACCESS 126
# define RETURN_COMMAND_NOT_FOUND 127
# define RETURN_CTRL_D 127
# define RETURN_SUSPENDED 146

/* Errors */

# define ERRTEMPLATE_SIMPLE "42sh: %s\n"
# define ERRTEMPLATE_NAMED "42sh: %s: %s\n"
# define ERRTEMPLATE_DOUBLE_NAMED "42sh: %s: %s: %s\n"
# define ERRTEMPLATE_DOUBLE_NAMED_QUOTED "42sh: %s: `%s': %s\n"

# define ERR_ENV_MISSING_TERM "No TERM environment variable set."
# define ERR_TERMCAP_NO_ACCESS "Unable to access termcap database."
# define ERR_TERMCAP_NO_ENTRY "No database entry for current terminal type."
# define ERR_WINDOW_TOO_SMALL "Window size is too small."
# define ERR_LINE_READ "input read error"
# define ERR_INPUT_CONTEXT_FAIL "failed to create input context"
# define ERR_CHILD_PROC_FAIL "cannot make child process"
# define ERR_CHILD_PIPE_FAIL "cannot make child pipes"
# define ERR_PIPE_FAIL "failed to create pipe"
# define ERR_HEREDOC_FAIL "failed to create heredoc"
# define ERR_DUP_FAIL "failed to duplicate file descriptor"
# define ERR_WRITE_BAD_FD "write error: Bad file descriptor"
# define ERR_COM_NOT_FOUND "command not found"
# define ERR_NO_PERMISSION "Permission denied"
# define ERR_TOO_FEW_ARGS "too few arguments"
# define ERR_NO_SUCH_FILE_OR_DIR "No such file or directory"
# define ERR_IS_DIR "is a directory"
# define ERR_IS_NOT_DIR "Not a directory"
# define ERR_CANNOT_GET_CWD "error retrieving current directory"
# define ERR_INVALID_PATH "path is invalid"
# define ERR_MALLOC_FAIL "memory allocation failed"
# define ERR_OPEN_FAIL "open failed"
# define ERR_WRITE_FAIL "write failed"
# define ERR_READ_FAIL "read failed"
# define ERR_TERMIOS_FAIL "failed to set terminal attributes"
# define ERR_NO_HOME "HOME not set"
# define ERR_NO_OLDPWD "OLDPWD not set"
# define ERR_SYNTAX "syntax error near unexpected token"
# define ERR_BAD_FD "bad file descriptor"
# define ERR_AMBIGUOUS_REDIR "ambiguous redirect"
# define ERR_NOT_VALID_ID "not a valid identifier"
# define ERR_STDIN_CLOSED "could not detect standard input"

/* Globals */

extern int				g_last_signal;

/* Types */

typedef struct s_input_initializer
{
	char	*start_prompt;
	char	*multiline_prompt;
	char	*mark;
	char	**reserved_sequences;
}	t_input_initializer;

typedef struct s_input_context
{
	char	*input;
	size_t	last_displayed_length;
	size_t	max_length;
	char	*mark;
	char	**reserved_sequences;
	char	found_reserved_sequence[BUF_SIZE + 1];
	char	*clipboard;
	char	*start_prompt;
	char	*multiline_prompt;
	size_t	cursor;
	size_t	input_start_x;
	size_t	input_start_y;
	size_t	width;
	size_t	height;
}	t_input_context;

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

typedef struct s_hash_entry
{
	unsigned long long	hash;
	char				*path;
	unsigned int		hits;
}	t_hash_entry;

typedef enum e_job_state
{
	JOB_EMPTY,
	JOB_CREATED,
	JOB_RUNNING,
	JOB_STOPPED,
	JOB_DONE
}	t_job_state;

typedef struct s_job
{
	int			id;
	t_job_state	state;
	bool		needs_status_print;
	pid_t		pids[MAX_PIDS];
	int			return_value;
	char		*command;
}	t_job;

typedef struct s_state
{
	char *const		*env;
	char *const		*intern;
	char *const		*exported;
	t_input_context	input_context;
	int				continue_previous_node;
	bool			in_quotes;
	t_token_type	quote_type;
	struct termios	input_conf;
	struct termios	orig_conf;
	bool			terminal_conf_applied;
	char			*history[HISTORY_SIZE];
	int				history_index;
	t_hash_entry	**hash_table;
	t_job			*current_job;
	t_job			jobs[MAX_JOBS];
	int				last_return_value;
	int				exit_return_value;
	int				exiting;
	bool			running_script;
}	t_state;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_tokenizer
{
	bool	in_quotes;
	bool	backslash_inhibited;
	char	quote_type;
	char	*buff;
	size_t	buff_idx;
}	t_tokenizer;

typedef enum e_ast_node_type
{
	AST_PIPE_SEQUENCE,
	AST_SIMPLE_COMMAND,
	AST_COMMAND_ARGS,
	AST_REDIRECTIONS
}	t_ast_node_type;

typedef struct s_ast_redir
{
	char	*redir_file;
	char	*redir_op;
	int		redir_fd;
	int		redir_fd_alias;
	bool	redir_out;
	bool	aggregation;
	int		agg_to;
	int		agg_from;
	bool	agg_close;
}	t_ast_redir;

typedef struct s_ast
{
	t_ast_node_type	node_type;
	char			**arg_list;
	char			**var_list;
	t_ast_redir		**redirs;
	int				and_or;
	bool			amp;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_pipes
{
	int	read[2];
	int	write[2];
}	t_pipes;

typedef struct s_redir
{
	int	saved_out;
	int	saved_err;
	int	saved_in;
	int	saved_fd;
	int	fd_agg;
	int	redir_fd;
}	t_redir;

typedef struct s_ast_context
{
	t_ast	*node;
	t_redir	**redirect;
	t_pipes	*pipes;
	bool	background;
	int		is_at_end;
}	t_ast_context;

#endif
