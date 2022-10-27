/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:28:16 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/26 11:45:55 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 * Calls fork(), sets up pipes, and resets signal handlers. Used to run both
 * built-ins and binaries.
 */
pid_t	start_fork(t_pipes *pipes)
{
	pid_t	result;

	if (pipes->read[0] != -1 && pipes->write[0] != -1)
	{
		if (dup2(pipes->write[PIPE_READ], pipes->read[PIPE_WRITE]) == -1)
			return (print_error(ERR_DUP_FAIL, -1));
	}
	result = fork();
	if (result == -1)
		return (print_error(ERR_CHILD_PROC_FAIL, -1));
	if (result != 0)
		return (result);
	if (!pipes_connect(pipes->read, pipes->write))
		exit(print_error(ERR_CHILD_PIPE_FAIL, 1));
	signal(SIGINT, SIG_DFL);
	return (result);
}
