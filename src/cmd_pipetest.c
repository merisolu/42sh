/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipetest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:41:28 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/24 12:56:53 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdio.h>

static void	connect_pipes(int read_pipe[2], int write_pipe[2])
{
	if (read_pipe[PIPE_READ] != -1)
	{
		if (dup2(read_pipe[PIPE_READ], STDIN_FILENO) == -1)
			perror("left pipe");
		close(read_pipe[PIPE_WRITE]);
		close(read_pipe[PIPE_READ]);
	}
	if (write_pipe[PIPE_READ] != -1)
	{
		if (dup2(write_pipe[PIPE_WRITE], STDOUT_FILENO) == -1)
			perror("right pipe");
		close(write_pipe[PIPE_READ]);
		close(write_pipe[PIPE_WRITE]);
	}
}

static pid_t	run_command(char *path, char *const *args, char *const *env, int read_pipe[2], int write_pipe[2])
{
	pid_t	pid;

	ft_dprintf(STDERR_FILENO, "Pipes: [%i, %i], [%i, %i]\n", read_pipe[0], read_pipe[1], write_pipe[0], write_pipe[1]);
	if (read_pipe[0] != -1 && write_pipe[0] != -1)
		dup2(write_pipe[PIPE_READ], read_pipe[PIPE_WRITE]);
	pid = fork();
	if (pid == -1)
		return (print_error(ERR_CHILD_PROC_FAIL, -1));
	if (pid > 0)
		return (pid);
	connect_pipes(read_pipe, write_pipe);
	signal(SIGINT, SIG_DFL);
	if (execve(path, args, env) == -1)
		exit(print_error(ERR_CHILD_PROC_FAIL, 1));
	return (0);
}

static pid_t	run_pipeline(char **commands, t_state *state)
{
	pid_t	result;
	size_t	length;
	int		read_pipe[2] = {-1, -1};
	int		write_pipe[2] = {-1, -1};

	length = ft_null_array_len((void *)commands);
	for (size_t i = 0; i < length; i++)
	{
		if (i < length - 1)
		{
			if (pipe(write_pipe) == -1)
				return (print_error("Failed to create pipe", 1));
		}
		else
		{
			write_pipe[PIPE_READ] = -1;
			write_pipe[PIPE_WRITE] = -1;
		}

		result = run_command(ft_strsplit(commands[i], ' ')[0], ft_strsplit(commands[i], ' '), state->env, read_pipe, write_pipe);

		close(read_pipe[PIPE_READ]);
		close(read_pipe[PIPE_WRITE]);

		read_pipe[PIPE_READ] = write_pipe[PIPE_READ];
		read_pipe[PIPE_WRITE] = write_pipe[PIPE_WRITE];
	}

	close(read_pipe[PIPE_READ]);
	close(read_pipe[PIPE_WRITE]);

	return (result);
}

// pipetest "/bin/ls -l /|/usr/bin/grep A|/usr/bin/wc -l"
int	cmd_pipetest(char *const *args, t_state *state)
{
	char	**commands;

	if (args[1] == NULL)
		return (1);

	commands = ft_strsplit(args[1], '|');
	waitpid(run_pipeline(commands, state), NULL, 0);
	return (0);
}
