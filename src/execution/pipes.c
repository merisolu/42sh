/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:55:10 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/29 13:10:43 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
 * Sets both ends of pipe to -1.
 */

void	pipe_reset(int pipe[2])
{
	pipe[PIPE_READ] = -1;
	pipe[PIPE_WRITE] = -1;
}

/*
 * Calls close() on both ends of the pipe.
 */

void	pipe_close(int pipe[2])
{
	if (pipe[PIPE_READ] != -1)
		close(pipe[PIPE_READ]);
	if (pipe[PIPE_WRITE] != -1)
		close(pipe[PIPE_WRITE]);
}

/*
 * Sets both ends of both pipes to -1.
 */

void	pipes_reset(int pipe1[2], int pipe2[2])
{
	pipe_reset(pipe1);
	pipe_reset(pipe2);
}

/*
 * Assigns target[PIPE_READ] to source[PIPE_READ], and target[PIPE_WRITE]
 * to source[PIPE_WRITE].
 */

void	pipes_copy(int target[2], const int source[2])
{
	target[PIPE_READ] = source[PIPE_READ];
	target[PIPE_WRITE] = source[PIPE_WRITE];
}

/*
 * Connects STDIN to the read end of read_pipe and STDOUT to the write end of
 * write_pipe. Returns 1 on success, 0 on error.
 */

int	pipes_connect(int read_pipe[2], int write_pipe[2])
{
	if (read_pipe[PIPE_READ] != -1)
	{
		if (dup2(read_pipe[PIPE_READ], STDIN_FILENO) == -1)
			print_error(ERR_DUP_FAIL, 0);
		close(read_pipe[PIPE_WRITE]);
		close(read_pipe[PIPE_READ]);
	}
	if (write_pipe[PIPE_READ] != -1)
	{
		if (dup2(write_pipe[PIPE_WRITE], STDOUT_FILENO) == -1)
			print_error(ERR_DUP_FAIL, 0);
		close(write_pipe[PIPE_READ]);
		close(write_pipe[PIPE_WRITE]);
	}
	return (1);
}
