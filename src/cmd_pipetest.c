/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipetest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:41:28 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/21 14:48:39 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdio.h>

static void	connect_pipes(int read_pipe[2], int write_pipe[2])
{
	if (read_pipe)
	{
		if (dup2(read_pipe[PIPE_READ], STDIN_FILENO) == -1)
			perror("left pipe");
		close(read_pipe[PIPE_WRITE]);
		close(read_pipe[PIPE_READ]);
	}
	if (write_pipe)
	{
		if (dup2(write_pipe[PIPE_WRITE], STDOUT_FILENO) == -1)
			perror("right pipe");
		close(write_pipe[PIPE_READ]);
		close(write_pipe[PIPE_WRITE]);
	}
}

int	cmd_pipetest(char *const *args, t_state *state)
{
	pid_t	ls_pid;
	char	*ls_args[4] = {"/bin/ls", "-l", "/", NULL};
	pid_t	grep_pid;
	char	*grep_args[3] = {"/usr/bin/grep", "A", NULL};
	pid_t	wc_pid;
	char	*wc_args[3] = {"/usr/bin/wc", "-l", NULL};

	int		ls_to_grep[2] = {-1, -1}; // Read, write
	int		grep_to_wc[2] = {-1, -1}; // Read, write

	(void)args;

	if (pipe(ls_to_grep) == -1)
		return (print_error("Failed to create pipe", 1));

	if (pipe(grep_to_wc) == -1)
		return (print_error("Failed to create pipe", 1));

	ls_pid = fork();
	if (ls_pid == -1)
		return (print_error(ERR_CHILD_PROC_FAIL, 1));
	if (ls_pid == 0)
	{
		connect_pipes(NULL, ls_to_grep);
		signal(SIGINT, SIG_DFL);
		if (execve(ls_args[0], ls_args, state->env) == -1)
			exit(print_error(ERR_CHILD_PROC_FAIL, 1));
	}

	dup2(grep_to_wc[PIPE_READ], ls_to_grep[PIPE_WRITE]);

	grep_pid = fork();
	if (grep_pid == -1)
		return (print_error(ERR_CHILD_PROC_FAIL, 1));
	if (grep_pid == 0)
	{
		connect_pipes(ls_to_grep, grep_to_wc);
		signal(SIGINT, SIG_DFL);
		if (execve(grep_args[0], grep_args, state->env) == -1)
			exit(print_error(ERR_CHILD_PROC_FAIL, 1));
	}

	wc_pid = fork();
	if (wc_pid == -1)
		return (print_error(ERR_CHILD_PROC_FAIL, 1));
	if (wc_pid == 0)
	{
		connect_pipes(grep_to_wc, NULL);
		signal(SIGINT, SIG_DFL);
		if (execve(wc_args[0], wc_args, state->env) == -1)
			exit(print_error(ERR_CHILD_PROC_FAIL, 1));
	}

	wait(NULL);

	close(ls_to_grep[0]);
	close(ls_to_grep[1]);
	close(grep_to_wc[0]);
	close(grep_to_wc[1]);

	return (0);
}
