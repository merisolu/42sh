/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:06:37 by amann             #+#    #+#             */
/*   Updated: 2022/12/05 14:20:38 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	reset_io(t_redir *r)
{
	if (r->saved_fd != -1)
	{
		if (dup2(r->saved_fd, r->fd_agg) == -1)
			return (print_error(0, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
		close(r->saved_fd);
		r->saved_fd = -1;
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
