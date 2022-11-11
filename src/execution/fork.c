/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:28:16 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/08 12:47:01 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
 * Calls fork(), sets up pipes, and resets signal handlers. Used to run both
 * built-ins and binaries.
 */
pid_t	start_fork(t_ast_execution *ast)
{
	pid_t	result;
	t_pipes	*pipes;

	pipes = ast->pipes;
	if (pipes->read[0] != -1 && pipes->write[0] != -1)
	{
		if (dup2(pipes->write[PIPE_READ], pipes->read[PIPE_WRITE]) == -1)
			return (print_error(ERR_DUP_FAIL, -1));
	}
	if (ast->node->right && !heredoc_run(ast->node->right, pipes))
		return (print_error(ERR_HEREDOC_FAIL, -1));
	result = fork();
	if (result == -1)
		return (print_error(ERR_CHILD_PROC_FAIL, -1));
	if (result != 0)
		return (result);
	if (!pipes_connect(pipes->read, pipes->write))
		exit(print_error(ERR_CHILD_PIPE_FAIL, 1));
	if (ast->node->right
		&& !handle_redirects(ast->node->right, ast->redirect))
		exit(1);
	signal(SIGINT, SIG_DFL);
	return (result);
}
