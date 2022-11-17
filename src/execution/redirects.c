/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:18:05 by amann             #+#    #+#             */
/*   Updated: 2022/11/16 17:26:52 by amann            ###   ########.fr       */
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

static bool	redirect_output(t_ast *redir_node, t_redir *r)
{
	int			append;
	static int	perms;

	perms = S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR | S_IROTH;
	append = O_TRUNC;
	if (ft_strequ(redir_node->out_type, REDIR_APPEND))
		append = O_APPEND;
	r->fd_out = open(redir_node->out_file, O_WRONLY | O_CREAT | append, perms);
	if (r->fd_out == -1)
	{
		if (ft_is_dir(redir_node->out_file))
			return (print_bool_named_error(redir_node->out_file,
					ERR_IS_DIR, false));
		return (print_bool_named_error(redir_node->out_file,
				ERR_NO_PERMISSION, false));
	}
	r->saved_out = dup(STDOUT_FILENO);
	if (r->saved_out == -1)
		return (print_bool_error(ERR_DUP_FAIL, false));
	if (dup2(r->fd_out, STDOUT_FILENO) == -1)
		return (print_bool_error(ERR_DUP_FAIL, false));
	close(r->fd_out);
	r->fd_out = -1;
	return (true);
}

static bool	redirect_input(t_ast *redir_node, t_redir *r)
{
	r->fd_in = open(redir_node->in_file, O_RDONLY);
	if (r->fd_in == -1)
	{
		if (access(redir_node->in_file, F_OK) == 0)
		{
			return (print_bool_named_error(redir_node->in_file,
					ERR_NO_PERMISSION, false));
		}
		return (print_bool_named_error(redir_node->in_file,
				ERR_NO_SUCH_FILE_OR_DIR, false));
	}
	r->saved_in = dup(STDIN_FILENO);
	if (r->saved_in == -1)
		return (print_bool_error(ERR_DUP_FAIL, false));
	if (dup2(r->fd_in, STDIN_FILENO) == -1)
		return (print_bool_error(ERR_DUP_FAIL, false));
	close(r->fd_in);
	r->fd_in = -1;
	return (true);
}

bool	handle_redirects(t_ast *redir_node, t_redir *r)
{
	if (redir_node->out_type)
	{
		if (!redirect_output(redir_node, r))
			return (false);
	}
	if (redir_node->in_type)
	{
		if (!ft_strequ(redir_node->in_type, REDIR_HEREDOC)
			&& !redirect_input(redir_node, r))
			return (false);
	}
	if (redir_node->aggregation)
	{
		if (!execute_filedes_aggregation(redir_node, r))
			return (false);
	}
	return (true);
}
