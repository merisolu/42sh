/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fd_aggregation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:31:16 by amann             #+#    #+#             */
/*   Updated: 2022/11/16 17:52:59 by amann            ###   ########.fr       */
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

int	execute_filedes_aggregation(t_ast *node, t_redir *r)
{
	if (!check_fd_errors(node))
		return (0);
	r->saved_fd = dup(node->agg_from);
	if (r->saved_fd == -1)
		return (print_error(ERR_DUP_FAIL, 0));
	r->fd_agg = node->agg_from;
	if (node->agg_close)
		close(node->agg_from);
	else
	{
		if (dup2(node->agg_to, node->agg_from) == -1)
			return (print_error(ERR_DUP_FAIL, 0));
	}
	return (1);
}
