/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:18:05 by amann             #+#    #+#             */
/*   Updated: 2022/11/11 13:54:21 by amann            ###   ########.fr       */
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
	{
		if (ft_is_dir(redir_node->out_file))
			return (print_named_error(redir_node->out_file, ERR_IS_DIR, 0));
		return (print_named_error(redir_node->out_file, ERR_NO_PERMISSION, 0));
	}
	r->saved_out = dup(STDOUT_FILENO);
	if (r->saved_out == -1)
		return (print_error(ERR_DUP_FAIL, 0));
	if (dup2(r->fd_out, STDOUT_FILENO) == -1)
		return (print_error(ERR_DUP_FAIL, 0));
	close(r->fd_out);
	r->fd_out = -1;
	return (1);
}

static int	redirect_input(t_ast *redir_node, t_redir *r)
{
	r->fd_in = open(redir_node->in_file, O_RDONLY);
	if (r->fd_in == -1)
	{
		if (access(redir_node->in_file, F_OK) == 0)
		{
			return (print_named_error(redir_node->in_file,
					ERR_NO_PERMISSION, 0));
		}
		return (print_named_error(redir_node->in_file,
				ERR_NO_SUCH_FILE_OR_DIR, 0));
	}
	r->saved_in = dup(STDIN_FILENO);
	if (r->saved_in == -1)
		return (print_error(ERR_DUP_FAIL, 0));
	if (dup2(r->fd_in, STDIN_FILENO) == -1)
		return (print_error(ERR_DUP_FAIL, 0));
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
