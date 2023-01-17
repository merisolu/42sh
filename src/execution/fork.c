/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:28:16 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/17 15:11:43 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
}

/*
 * Calls fork(), sets up pipes, and resets signal handlers. Used to run both
 * built-ins and binaries.
 */

pid_t	start_fork(t_ast_context *ast)
{
	pid_t	result;

	if (ast && ast->pipes->read[0] != -1 && ast->pipes->write[0] != -1)
	{
		if (dup2(ast->pipes->write[PIPE_READ],
				ast->pipes->read[PIPE_WRITE]) == -1)
			return (print_error(
					-1, ERRTEMPLATE_SIMPLE, ERR_DUP_FAIL));
	}
	result = fork();
	if (result == -1)
		return (print_error(
				-1, ERRTEMPLATE_SIMPLE, ERR_CHILD_PROC_FAIL));
	if (result != 0)
		return (result);
	if (ast && !pipes_connect(ast->pipes->read, ast->pipes->write))
		exit(print_error(
				1, ERRTEMPLATE_SIMPLE, ERR_CHILD_PIPE_FAIL));
	if (ast && ast->node->right
		&& !handle_redirects(ast->node->right, ast->redirect))
		exit(1);
	reset_signals();
	return (result);
}

/*
 * Returns true if the pipes are set up to go somewhere, false otherwise.
 */

bool	in_pipes(t_pipes *pipes)
{
	return (!(pipes->read[0] == -1 && pipes->read[1] == -1
			&& pipes->write[0] == -1 && pipes->write[1] == -1));
}
