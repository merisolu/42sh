/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fd_aggregation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:31:16 by amann             #+#    #+#             */
/*   Updated: 2022/12/16 15:03:10 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	find_aliased_fd(t_ast_redir **head, int *fd)
{
	int i;

	i = 0;
	while (head[i])
	{
		//ft_printf("%d %d %d\n", (head[i])->redir_fd, (head[i])->redir_fd_alias,*fd);
		if ((head[i])->redir_fd == *fd)
		{
			*fd = (head[i])->redir_fd_alias;
			return (true);
		}
		i++;
	}
	return (false);
}

/*
 * If an unused fd is quoted to copy from in the shell, this would normally be
 * opened for reading. However, we are not allowed to use fdopen() in this
 * project, so we cannot open fd's by their actual number, we need a filepath.
 * Because of this limitation, we can just return an error if fstat() finds
 * that the fd on either side of the >& operator is closed
 */

static bool	check_fd_errors(t_ast_redir **redir, t_ast_redir **head)
{
	struct stat	buf;

	if (fstat((*redir)->agg_to, &buf) == -1 || ((*redir)->agg_to > 2
		&& !find_aliased_fd(head, &((*redir)->agg_to))))
	{
			return (print_error_bool(
				false, "21sh: %i: %s\n", (*redir)->agg_to, ERR_BAD_FD));
	}
	if (fstat((*redir)->agg_from, &buf) == -1)
	{
		return (print_error_bool(
				false, "21sh: %i: %s\n", (*redir)->agg_from, ERR_BAD_FD));
	}
	return (true);
}

static bool already_aggregated(t_redir **head, int fd)
{
	int i;

	i = 0;
	while (head[i])
	{
		if ((head[i])->fd_agg == fd)
			return (true);
		i++;
	}
	return (false);
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

bool	execute_filedes_aggregation(t_ast_redir **redir, t_redir *r, t_ast_redir **head, t_redir **r_head)
{
	if (!check_fd_errors(redir, head))
		return (false);
	if (!already_duped(r_head, (*redir)->agg_from)
			&& !already_aggregated(r_head, (*redir)->agg_from))
	{
		r->saved_fd = dup((*redir)->agg_from);
		if (r->saved_fd == -1)
		{
			return (print_error(
					false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
		}
		r->fd_agg = (*redir)->agg_from;
	}
	if ((*redir)->agg_close)
		close((*redir)->agg_from);
	else
	{
		if (dup2((*redir)->agg_to, (*redir)->agg_from) == -1)
		{
			return (print_error(
					false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
		}
	}
	if (r->saved_fd < 3)
		close(r->saved_fd);
	return (true);
}
