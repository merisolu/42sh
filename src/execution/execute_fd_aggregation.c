/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fd_aggregation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:31:16 by amann             #+#    #+#             */
/*   Updated: 2022/12/02 17:48:11 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

bool	execute_filedes_aggregation(t_ast_redir *redir, t_redir *r)
{
	if (!check_fd_errors(redir))
		return (false);
	r->saved_fd = dup(redir->agg_from);
	if (r->saved_fd == -1)
		return (print_error(
				false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
	r->fd_agg = redir->agg_from;
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
