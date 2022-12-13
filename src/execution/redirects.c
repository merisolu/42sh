/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:18:05 by amann             #+#    #+#             */
/*   Updated: 2022/12/13 15:50:57 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	initialize_redir_struct(t_redir *r)
{
	r->fd_out = -1;
	r->fd_in = -1;
	r->fd_err = -1;
	r->saved_out = -1;
	r->saved_in = -1;
	r->saved_err = -1;
	r->saved_fd = -1;
	r->fd_agg = -1;
	r->reset_order = -1;
}

/*
static bool	redirect_input(t_ast_redir *redir_node, t_redir *r)
{
	if (r->saved_in == -1 && !copy_orig_fd(&(r->saved_in), STDIN_FILENO))
		return (false);
	r->fd_in = open(redir_node->in_file, O_RDONLY);
	if (r->fd_in == -1)
	{
		if (access(redir_node->in_file, F_OK) == 0)
		{
			return (print_error_bool(
					false, ETEMPLATE_SHELL_NAMED,
					redir_node->in_file, ERR_NO_PERMISSION));
		}
		return (print_error_bool(
				false, ETEMPLATE_SHELL_NAMED,
				redir_node->in_file, ERR_NO_SUCH_FILE_OR_DIR));
	}
	if (dup2(r->fd_in, STDIN_FILENO) == -1)
		return (print_error_bool(
				false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
	close(r->fd_in);
	r->fd_in = -1;
	r->reset_order = 0;
	return (true);
}

static bool	redirect_output(t_ast_redir *redir, t_redir *r)
{
	int			append;
	static int	perms;

	if (r->saved_out == -1 && !copy_orig_fd(&(r->saved_out), STDOUT_FILENO))
		return (false);
	perms = S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR | S_IROTH;
	append = O_TRUNC;
	if (ft_strequ(redir->out_type, REDIR_APPEND))
		append = O_APPEND;
	r->fd_out = open(redir->out_file, O_WRONLY | O_CREAT | append, perms);
	if (r->fd_out == -1)
	{
		if (ft_is_dir(redir->out_file))
			return (print_error_bool(false, ETEMPLATE_SHELL_NAMED,
					redir->out_file, ERR_IS_DIR));
		return (print_error_bool(false, ETEMPLATE_SHELL_NAMED,
				redir->out_file, ERR_NO_PERMISSION));
	}
//	dup2(r->fd_out, 7);
	if (dup2(r->fd_out, STDOUT_FILENO) == -1)
		return (print_error_bool(false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
	close(r->fd_out);
	r->fd_out = -1;
	r->reset_order = 0;
	return (true);
}

static bool	redirect_error(t_ast_redir *redir, t_redir *r)
{
	int			append;
	static int	perms;

	if (r->saved_err == -1 && !copy_orig_fd(&(r->saved_err), STDERR_FILENO))
		return (false);
	perms = S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR | S_IROTH;
	append = O_TRUNC;
	if (ft_strequ(redir->err_type, REDIR_APPEND))
		append = O_APPEND;
	r->fd_err = open(redir->err_file, O_WRONLY | O_CREAT | append, perms);
	if (r->fd_err == -1)
	{
		if (ft_is_dir(redir->err_file))
			return (print_error_bool(false, ETEMPLATE_SHELL_NAMED,
					redir->err_file, ERR_IS_DIR));
		return (print_error_bool(false, ETEMPLATE_SHELL_NAMED,
				redir->err_file, ERR_NO_PERMISSION));
	}
	if (dup2(r->fd_err, STDERR_FILENO) == -1)
		return (print_error_bool(false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
	close(r->fd_err);
	r->fd_err = -1;
	r->reset_order = 0;
	return (true);
}*/

static bool	copy_orig_fd(t_ast_redir *redir, t_redir **r)
{
	if (ft_strequ(redir->redir_op, ">") || ft_strequ(redir->redir_op, ">>") || ft_strequ(redir->redir_op, ">&"))
	{
		if (redir->redir_fd == STDERR_FILENO)
			(*r)->saved_err = dup(STDERR_FILENO);
		else
			(*r)->saved_out = dup(STDOUT_FILENO);
	}
	else
		(*r)->saved_in = dup(STDIN_FILENO);
	if ((*r)->saved_err == -1 && (*r)->saved_out == -1 && (*r)->saved_in == -1)
		return (print_error_bool(false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
	return (true);
}

static bool	execute_redirection(t_ast_redir *redir, t_redir *r)
{
	int			open_flags;
	int			perm;
	int			fd;

	if (!copy_orig_fd(redir, &r))
		return (false);

	if (ft_strequ(redir->redir_op, ">") || ft_strequ(redir->redir_op, ">&") || ft_strequ(redir->redir_op, REDIR_APPEND))
	{
		if (!open_output_file())
			return (false);

		open_flags = O_WRONLY | O_CREAT;
		if (ft_strequ(redir->redir_op, REDIR_APPEND))
			open_flags |= O_APPEND;
		else
			open_flags |= O_TRUNC;
		perm = 0644;
	}
	else
	{
		open_flags = O_RDONLY;
		perm = 0450;
	}
	fd = open(redir->out_file, open_flags, perm);
	if (fd == -1)
	{
		if (ft_is_dir(redir->out_file))
			return (print_error_bool(false, ETEMPLATE_SHELL_NAMED,
					redir->out_file, ERR_IS_DIR));
		if (access(redir_node->in_file, F_OK) == 0)
		{
			return (print_error_bool(
					false, ETEMPLATE_SHELL_NAMED,
					redir_node->in_file, ERR_NO_PERMISSION));
		}
		return (print_error_bool(false, ETEMPLATE_SHELL_NAMED,
				redir->out_file, ERR_NO_PERMISSION));
	}

//	dup2(r->fd_out, 7);
	if (dup2(r->fd_out, STDOUT_FILENO) == -1)
		return (print_error_bool(false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));

	close(r->fd_out);
	r->fd_out = -1;
	r->reset_order = 0;
	return (true);
}

bool	handle_redirects(t_ast *node, t_redir *r)
{
	size_t	i;

	if (!node->redirs)
		return (true);
	i = 0;
	while (node->redirs[i])
	{
		if (node->redirs[i]->aggregation)
		{
			if (!execute_filedes_aggregation(node->redirs[i], r))
				return (false);
		}
		else
		{
			if (!execute_redirection(node->redirs[i], r))
				return (false);
		}
		i++;
	}
	ast_free_redirs(&node);
	return (true);
}
