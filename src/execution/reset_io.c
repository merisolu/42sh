/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:06:37 by amann             #+#    #+#             */
/*   Updated: 2022/12/15 15:41:52 by amann            ###   ########.fr       */
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
		if (r->saved_fd > 2)
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
		if (r->saved_err > 2)
			close(r->saved_err);
		r->saved_err = -1;
	}
	if (r->saved_out != -1)
	{
		if (dup2(r->saved_out, STDOUT_FILENO) == -1)
			return (print_error(0, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
		if (r->saved_out > 2)
			close(r->saved_out);
		r->saved_out = -1;
	}
	if (r->saved_in != -1)
	{
		if (dup2(r->saved_in, STDIN_FILENO) == -1)
			return (print_error(0, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
		if (r->saved_in > 2)
			close(r->saved_in);
		r->saved_in = -1;
	}
	return (1);
}

//TODO make this an array of structs
int	reset_io(t_redir **r)
{
	int i;

	i = 0;
	while (r[i])
	{
		debug_redir(NULL, r[i]);
		reset_redirs(r[i]);
		reset_fd_aggregation(r[i]);
		if ((r[i])->redir_fd > 2)
			close((r[i])->redir_fd);
		free(r[i]);
		i++;
	}

	return (1);
}
