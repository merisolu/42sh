/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fd_aggregation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:31:16 by amann             #+#    #+#             */
/*   Updated: 2023/01/05 15:58:14 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	find_aliased_fd(t_ast_redir **head, int *fd)
{
	int		i;
	int		check;
	bool	found;

	found = false;
	check = *fd;
	i = 0;
	while (head[i])
	{
		if ((head[i])->redir_fd == check)
		{
			*fd = (head[i])->redir_fd_alias;
			found = true;
		}
		i++;
	}
	return (found);
}

static bool	already_aggregated(t_redir **head, int fd)
{
	int	i;

	i = 0;
	while (head[i])
	{
		if ((head[i])->fd_agg == fd)
			return (true);
		i++;
	}
	return (false);
}

static bool	dup_or_close(t_ast_redir **redir, t_ast_redir **head, t_redir **r_h)
{
	int	orig;

	if ((*redir)->agg_close)
		close((*redir)->agg_from);
	else
	{
		orig = (*redir)->agg_to;
		find_aliased_fd(head, &((*redir)->agg_to));
		if (!fd_is_open((*redir)->agg_to) || ((*redir)->agg_to > 2
				&& !find_aliased_fd(head, &orig)
				&& !already_aggregated(r_h, (*redir)->agg_to)))
			return (print_error_bool(
					false, "42sh: %i: %s\n", (*redir)->agg_to, ERR_BAD_FD));
		if (dup2((*redir)->agg_to, (*redir)->agg_from) == -1)
		{
			return (print_error(
					false, ERRTEMPLATE_SIMPLE, ERR_DUP_FAIL));
		}
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

bool	execute_filedes_aggregation(t_ast_redir **redir, t_redir *r, \
		t_ast_redir **head, t_redir **r_head)
{
	if (fd_is_open((*redir)->agg_from)
		&& !already_duped(r_head, (*redir)->agg_from))
	{
		r->saved_fd = dup((*redir)->agg_from);
		if (r->saved_fd == -1)
		{
			return (print_error(
					false, ERRTEMPLATE_SIMPLE, ERR_DUP_FAIL));
		}
	}
	else
		r->saved_fd = (*redir)->agg_from;
	r->fd_agg = (*redir)->agg_from;
	if (r->saved_fd < 3)
		close(r->saved_fd);
	if (!dup_or_close(redir, head, r_head))
		return (false);
	return (true);
}
