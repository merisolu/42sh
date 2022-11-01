/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:18:05 by amann             #+#    #+#             */
/*   Updated: 2022/11/01 15:56:27 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	initialize_redir_struct(t_redir *r)
{
	r->fd_out = -1;
	r->fd_in = -1;
	r->saved_out = -1;
	r->saved_in = -1;
	r->saved_fd = -1;
	r->fd_agg = -1;
}
/*
	int fd;
	int permissions = S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR | S_IROTH;
	fd = open("svout", O_WRONLY | O_CREAT | O_APPEND, permissions);
	ft_dprintf(fd, "\n***\nsvout = %d\nsvin = %d\nsvfd = %d\nfdout = \
	%d\nfdin = %d\n", r->saved_out, r->saved_in, r->saved_fd,
	r->fd_out, r->fd_in);
	close(fd);
*/

int	reset_io(t_redir *r)
{
	if (r->saved_fd != -1)
	{
		if (dup2(r->saved_fd, r->fd_agg) == -1)
			return (print_error("could not dup2! (paceholder)\n", 0));
		close(r->saved_fd);
		r->saved_fd = -1;
	}
	if (r->saved_out != -1)
	{
		if (dup2(r->saved_out, STDOUT_FILENO) == -1)
			return (print_error("could not dup2 (paceholder)\n", 0));
		close(r->saved_out);
		r->saved_out = -1;
	}
	if (r->saved_in != -1)
	{
		if (dup2(r->saved_in, STDIN_FILENO) == -1)
			return (print_error("could not dup2! (paceholder)\n", 0));
		close(r->saved_in);
		r->saved_in = -1;
	}
	return (1);
}

static int	redirect_output(t_ast *redir_node, t_redir *r)
{
	int			append;
	static int	o_flags;
	static int	permissions;

	o_flags = O_WRONLY | O_CREAT;
	permissions = S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR | S_IROTH;
	append = O_TRUNC;
	if (ft_strequ(redir_node->out_type, REDIR_APPEND))
		append = O_APPEND;
	r->fd_out = open(redir_node->out_file, o_flags | append, permissions);
	if (r->fd_out == -1)
		return (print_error("could not open! (paceholder)\n", 0));
	r->saved_out = dup(STDOUT_FILENO);
	if (r->saved_out == -1)
		return (print_error("could not dup! (paceholder)\n", 0));
	if (dup2(r->fd_out, STDOUT_FILENO) == -1)
		return (print_error("could not dup2! (paceholder)\n", 0));
	close(r->fd_out);
	r->fd_out = -1;
	return (1);
}

/*
 * TODO heredocs
 * check permissions if file cannot be opened or read
 * check error messages needed for issues with dup...
 */

static int	redirect_input(t_ast *redir_node, t_redir *r)
{
	r->fd_in = open(redir_node->in_file, O_RDONLY);
	if (r->fd_in == -1)
		return (print_error(ERR_NO_SUCH_FILE_OR_DIR, 0));
	r->saved_in = dup(STDIN_FILENO);
	if (r->saved_in == -1)
		return (print_error("could not dup! (paceholder)\n", 0));
	if (dup2(r->fd_in, STDIN_FILENO) == -1)
		return (print_error("could not dup2! (paceholder)\n", 0));
	close(r->fd_in);
	r->fd_in = -1;
	return (1);
}

int	handle_redirects(t_ast *redir_node, t_redir *r)
{
	if (redir_node->out_type)
	{
		if (!redirect_output(redir_node, r))
			return (0);
	}
	if (redir_node->in_type)
	{
		if (!redirect_input(redir_node, r))
			return (0);
	}
	if (redir_node->aggregation)
	{
		if (!execute_filedes_aggregation(redir_node, r))
			return (0);
	}
	return (1);
}
