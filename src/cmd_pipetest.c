/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipetest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:41:28 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/21 15:06:48 by jumanner         ###   ########.fr       */
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

static int	run_command(char *path, char *const *args, char *const *env, int read_pipe[2], int write_pipe[2])
{
	pid_t	pid;

	if (read_pipe && write_pipe)
		dup2(write_pipe[PIPE_READ], read_pipe[PIPE_WRITE]);
	pid = fork();
	if (pid == -1)
		return (print_error(ERR_CHILD_PROC_FAIL, -1));
	if (pid > 0)
		return (0);
	connect_pipes(read_pipe, write_pipe);
	signal(SIGINT, SIG_DFL);
	if (execve(path, args, env) == -1)
		exit(print_error(ERR_CHILD_PROC_FAIL, 1));
	return (1);
}

int	cmd_pipetest(char *const *args, t_state *state)
{
	char	*ls_args[4] = {"/bin/ls", "-l", "/", NULL};
	char	*grep_args[3] = {"/usr/bin/grep", "A", NULL};
	char	*wc_args[3] = {"/usr/bin/wc", "-l", NULL};

	int		ls_to_grep[2] = {-1, -1}; // Read, write
	int		grep_to_wc[2] = {-1, -1}; // Read, write

	(void)args;

	if (pipe(ls_to_grep) == -1)
		return (print_error("Failed to create pipe", 1));

	if (pipe(grep_to_wc) == -1)
		return (print_error("Failed to create pipe", 1));

	run_command(ls_args[0], ls_args, state->env, NULL, ls_to_grep);
	run_command(grep_args[0], grep_args, state->env, ls_to_grep, grep_to_wc);
	run_command(wc_args[0], wc_args, state->env, grep_to_wc, NULL);

	wait(NULL);

	close(ls_to_grep[0]);
	close(ls_to_grep[1]);
	close(grep_to_wc[0]);
	close(grep_to_wc[1]);

	return (0);
}
