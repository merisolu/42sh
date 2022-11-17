/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:28:16 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/17 15:43:55 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
			return (print_error(ERR_DUP_FAIL, -1));
	}
	result = fork();
	if (result == -1)
		return (print_error(ERR_CHILD_PROC_FAIL, -1));
	if (result != 0)
		return (result);
	if (ast && !pipes_connect(ast->pipes->read, ast->pipes->write))
		exit(print_error(ERR_CHILD_PIPE_FAIL, 1));
	if (ast && ast->node->right
		&& !handle_redirects(ast->node->right, ast->redirect))
		exit(1);
	signal(SIGINT, SIG_DFL);
	return (result);
}
