/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fd_aggregation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:31:16 by amann             #+#    #+#             */
/*   Updated: 2022/11/01 15:32:18 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_fd_errors(t_ast *node)
{
	struct stat	buf;

	if (fstat(node->agg_to, &buf) == -1)
	{
		ft_dprintf(
			STDERR_FILENO,
			"21sh: %d: bad file descriptor\n",
			node->agg_to
			);
		return (0);
	}
	if (fstat(node->agg_from, &buf) == -1)
	{
		ft_dprintf(
			STDERR_FILENO,
			"21sh: %d: bad file descriptor\n",
			node->agg_from
			);
		return (0);
	}
	return (1);
}

/*
 * >&- or <&-
 * >&2 or <&2
 * 2>&1
 *
 * if there are several redirections, they are processed from left to right
 *
 * [n]>&word
 * If word evaluates to one or more digits, the file descriptor denoted by n,
 * or standard output if n is not specified, shall be made to be a copy of the
 * file descriptor denoted by word;
 *
 * >& alone causes segfault
 */

int	execute_filedes_aggregation(t_ast *node, t_redir *r)
{
	if (!check_fd_errors(node))
		return (0);
	r->saved_fd = dup(node->agg_from);
	if (r->saved_fd == -1)
		return (0);
	r->fd_agg = node->agg_from;
	if (node->agg_close)
		close(node->agg_from);
	else
	{
		if (dup2(node->agg_to, node->agg_from) == -1)
			return (0);
	}
	return (1);
}
