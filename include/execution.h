/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:11 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 15:17:11 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

/* Includes */

# include <fcntl.h>

# if __linux__
#  include <signal.h>
#  include <sys/wait.h>
# endif

# include "libft.h"
# include "general.h"
# include "utils.h"
# include "environment.h"
# include "built_ins.h"
# include "ast.h"
# include "history.h"
# include "input.h"

/* Constants */
# define REDIR_APPEND ">>"
# define REDIR_HEREDOC "<<"

/* Types */

typedef struct s_redir
{
	int	fd_out;
	int	fd_in;
	int	saved_out;
	int	saved_in;
}	t_redir;

typedef struct s_ast_execution
{
	t_ast	*node;
	t_redir	*redirect;
	t_pipes	*pipes;
	int		is_at_end;
}	t_ast_execution;

/* Files */

/* bin.c */
int		bin_env_find(const char *name, char *const *env, char **result);
pid_t	bin_execute(char *path, char **args, char *const *env, t_pipes *pipes);

/* executor.c */
pid_t	execute(char *const *args, t_state *state, t_pipes *pipes);

/* fork.c */
pid_t	start_fork(t_pipes *pipes);

/* pipes.c */
void	pipe_reset(int pipe[2]);
void	pipe_close(int pipe[2]);
void	pipes_reset(int pipe1[2], int pipe2[2]);
int		pipes_connect(int read_pipe[2], int write_pipe[2]);
void	pipes_copy(int target[2], int source[2]);

/* redirects.c */
void	initialize_redir_struct(t_redir *r);
int		reset_io(t_redir r);
int		handle_redirects(t_ast *redir_node, t_redir *r);

/* tokenize_and_execute.c */
void	tokenize_and_execute(t_state *state);

#endif
