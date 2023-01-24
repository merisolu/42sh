/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:11 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/24 11:11:14 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

/* Includes */

# if __linux__
#  include <signal.h>
#  include <sys/wait.h>
# endif

# include "cursor.h"
# include "display.h"
# include "expansion.h"
# include "ast.h"
# include "history.h"
# include "terminal.h"
# include "signals.h"
# include "debug.h"

/* Constants */
# define JOB_BACKGROUND_CREATED_PRINT "[%d] %d\n"

# define JOB_PRINT_START "[%d]%c\t"
# define JOB_PRINT_START_LONG "[%d]%c\t%d "
# define JOB_PRINT_END "\t\t%s\n"
# define JOB_PID_PRINT "%d\n"

/* Files */

/* bin.c */
int		bin_env_find(const char *name, t_state *state, char **result);
void	bin_execve(char *path, char **args, char *const *env);

int		bin_env_find_silent(const char *name, t_state *state, char **result);

/* copy_orig_fd.c */
bool	copy_orig_fd(t_ast_redir *redir, t_redir **r, t_redir **head);

/* executor.c */
int		execute(char *const *args, t_state *state, t_ast_context *ast);

/* executor_path_utils.c */
int		check_path_validity(char *path);
int		find_binary(char *name, t_state *state, char **path, bool silent);
bool	path_exists(t_state *state);

/* execute_fd_aggregation.c */
bool	execute_filedes_aggregation(t_ast_redir **redir, t_redir *r, \
		t_ast_redir **head, t_redir **r_head);

/* execute_redirection.c */
bool	execute_redirection(t_ast_redir *redir, t_redir *r, t_redir **head);

/* execute_simple_command.c */
pid_t	execute_simple_command(t_ast_context *ctx, t_state *state);

/* fork.c */
pid_t	start_fork(t_ast_context *ast);
bool	in_pipes(t_pipes *pipes);

/* handle_logical_ops.c */
void	handle_logical_ops(t_ast **ast, t_state *state, int *i);

/* heredocs.c */
int		heredoc_run(t_ast *redir_node, t_pipes *pipes);

/* pids.c */
bool	pids_add(pid_t pid, t_job *job);
void	pid_wait(t_job *job, pid_t pid, bool non_blocking);
void	pids_clean_up(t_job *job);

/* jobs.c */
t_job	*jobs_create(t_state *state);
void	job_wait(t_job *job, bool non_blocking, t_state *state);
void	jobs_check_status(t_state *state);
void	jobs_print_changed(t_state *state);
void	jobs_cleanup_finished(t_state *state);

/* jobs_print.c */
void	job_print(t_job *job, char format, t_state *state);

/* jobs_utils.c */
pid_t	job_get_last_pid(t_job *job);
void	job_current_update(t_job *new_current, t_state *state);
void	job_execute(t_job *job, bool background, t_state *state);

/* jobs_print.c */
t_job	*job_id_to_job(char *id, t_state *state);

/* process_group.c */
pid_t	process_group_set(pid_t pid, pid_t job_first_pid, bool foreground);

/* pipes.c */
void	pipe_reset(int pipe[2]);
void	pipe_close(int pipe[2]);
void	pipes_reset(int pipe1[2], int pipe2[2]);
int		pipes_connect(int read_pipe[2], int write_pipe[2]);
void	pipes_copy(int target[2], const int source[2]);

/* redirects.c */
void	initialize_redir_struct(t_redir *r);
bool	already_duped(t_redir **head, int fd);
bool	handle_redirects(t_ast *redir_node, t_redir **r);

/* remove_temp_vars.c */
bool	remove_temp_vars_from_env(t_ast_context *ctx, t_state *state);

/* reset_io.c */
int		reset_io(t_redir **r);

/* set_internal_variables.c */
bool	set_internal_variables(char **var_list, t_state *state);

/* tokenize_and_execute.c */
void	tokenize_and_execute(t_state *state);

/* update_env_execution.c */
bool	update_env_execution(t_state *state, t_ast_context *ctx);
#endif
