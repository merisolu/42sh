/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:06:37 by amann             #+#    #+#             */
/*   Updated: 2022/12/14 16:28:43 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

#include "utils.h"

static int	reset_fd_aggregation(t_redir *r)
{
	if (r->saved_fd != -1)
	{
		if (dup2(r->saved_fd, r->fd_agg) == -1)
			return (print_error(0, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
		close(r->saved_fd);
		r->saved_fd = -1;
	}
	return (1);
}

static int	reset_redirs(t_redir *r)
{
	if (r->saved_err != -1)
	{
		if (dup2(r->saved_err, STDERR_FILENO) == -1)
			return (print_error(0, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
		close(r->saved_err);
		r->saved_err = -1;
	}
	if (r->saved_out != -1)
	{
		if (dup2(r->saved_out, STDOUT_FILENO) == -1)
			return (print_error(0, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
		close(r->saved_out);
		r->saved_out = -1;
	}
	if (r->saved_in != -1)
	{
		if (dup2(r->saved_in, STDIN_FILENO) == -1)
			return (print_error(0, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
		close(r->saved_in);
		r->saved_in = -1;
	}
	return (1);
}

int	reset_io(t_redir *r)
{
	debug_redir(NULL, r);
	ft_printf("%d\n", r->reset_order);
	if (r->reset_order == 1)
	{
		reset_fd_aggregation(r);
		reset_redirs(r);
	}
	else
	{
		reset_redirs(r);
		reset_fd_aggregation(r);
	}
	return (1);
}
