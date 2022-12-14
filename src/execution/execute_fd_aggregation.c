/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fd_aggregation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:31:16 by amann             #+#    #+#             */
/*   Updated: 2022/12/14 14:34:16 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 * If an unused fd is quoted to copy from in the shell, this would normally be
 * opened for reading. However, we are not allowed to use fdopen() in this
 * project, so we cannot open fd's by their actual number, we need a filepath.
 * Because of this limitation, we can just return an error if fstat() finds
 * that the fd on either side of the >& operator is closed
 */

static bool	check_fd_errors(t_ast_redir *redir)
{
	struct stat	buf;

	if (fstat(redir->agg_to, &buf) == -1)
	{
		return (print_error_bool(
				false, "21sh: %i: %s\n", redir->agg_to, ERR_BAD_FD));
	}
	if (fstat(redir->agg_from, &buf) == -1)
	{
		return (print_error_bool(
				false, "21sh: %i: %s\n", redir->agg_from, ERR_BAD_FD));
	}
	return (true);
}

/*
 * As with redirections, in fd aggregation we need to ensure that we only
 * save the fd we are copying once. If we were recreating the full behaviour
 * of bash, each fd aggreation operation in each command would probably need
 * to have the left operand saved with dup, but this is fine for our purposes.
 *
 * We have to save the copied fd into the t_redir struct so it can be reset
 * properly.
 *
 * If we are closing the specified fd, we can simply close(fd), otherwise, we
 * need dup2 to copy the output to the fd specified as the right operand.
 */

bool	execute_filedes_aggregation(t_ast_redir *redir, t_redir *r)
{
	if (!check_fd_errors(redir))
		return (false);
	if (r->saved_fd == -1)
		r->saved_fd = dup(redir->agg_from);
	if (r->saved_fd == -1)
		return (print_error(
				false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
	r->fd_agg = redir->agg_from;
	r->reset_order = 1;
	if (redir->agg_close)
		close(redir->agg_from);
	else
	{
		if (dup2(redir->agg_to, redir->agg_from) == -1)
			return (print_error(
					false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
	}
	return (true);
}
