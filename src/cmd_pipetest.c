/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipetest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:41:28 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/20 14:55:22 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	cmd_pipetest(char *const *args, t_state *state)
{
	pid_t	ls_pid;
	char	*ls_args[4] = {"/bin/ls", "-l", "/", NULL};
	pid_t	wc_pid;
	char	*wc_args[3] = {"/usr/bin/wc", "-l", NULL};
	int		pipe_file_des[2] = {-1, -1}; // Read, write

	(void)args;

	if (pipe(pipe_file_des) == -1)
	{
		ft_dprintf(STDERR_FILENO, "Error message");
		return (1);
	}

	ls_pid = fork();
	if (ls_pid == -1)
		return (1);
	if (ls_pid == 0)
	{
		close(pipe_file_des[PIPE_READ]);
		dup2(pipe_file_des[PIPE_WRITE], STDOUT_FILENO);

		signal(SIGINT, SIG_DFL);

		if (execve(ls_args[0], ls_args, state->env) == -1)
			exit(print_error(ERR_CHILD_PROC_FAIL, 1));
	}

	wc_pid = fork();
	if (wc_pid == -1)
		return (1);
	if (wc_pid == 0)
	{
		close(pipe_file_des[PIPE_WRITE]);
		dup2(pipe_file_des[PIPE_READ], STDIN_FILENO);

		signal(SIGINT, SIG_DFL);

		if (execve(wc_args[0], wc_args, state->env) == -1)
			exit(print_error(ERR_CHILD_PROC_FAIL, 1));
	}

	wait(NULL);

	close(pipe_file_des[0]);
	close(pipe_file_des[1]);

	return (0);
}
