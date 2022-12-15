/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:18:05 by amann             #+#    #+#             */
/*   Updated: 2022/12/15 16:42:47 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	initialize_redir_struct(t_redir *r)
{
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

static bool	fd_is_open(int fd)
{
	struct stat buf;

	if (fstat(fd, &buf) == -1)
		return (false);
	return (true);
}

static bool	dup_fd(int fd, int *i)
{

	if (!fd_is_open(fd))
		return (print_error_bool(
			false, "21sh: %i: %s\n", fd, ERR_BAD_FD));
	if (*i == -1)
		*i = dup(fd);
	if (*i == -1)
		return (print_error_bool(false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
	return (true);
}

static bool	copy_orig_fd(t_ast_redir *redir, t_redir **r)
{
	if (redir->redir_out)
	{
		if (redir->redir_fd == STDERR_FILENO)
		{
			return (dup_fd(STDERR_FILENO, &((*r)->saved_err)));
		}
		else
			return (dup_fd(STDOUT_FILENO, &((*r)->saved_out)));
	}
	else
		return (dup_fd(STDIN_FILENO, &((*r)->saved_in)));
}

static bool	execute_redirection(t_ast_redir *redir, t_redir *r)
{
	int			open_flags;
	int			perm;
	int			fd;

	if ((redir->redir_fd == -1 || redir->redir_fd == 2) && !copy_orig_fd(redir, &r))
		return (false);

	if (redir->redir_out)
	{
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
	fd = open(redir->redir_file, open_flags, perm);
	if (fd == -1)
	{
		if (ft_is_dir(redir->redir_file))
			return (print_error_bool(false, ETEMPLATE_SHELL_NAMED,
					redir->redir_file, ERR_IS_DIR));
		if (access(redir->redir_file, F_OK) == 0)
		{
			return (print_error_bool(
					false, ETEMPLATE_SHELL_NAMED,
					redir->redir_file, ERR_NO_PERMISSION));
		}
		return (print_error_bool(false, ETEMPLATE_SHELL_NAMED,
				redir->redir_file, ERR_NO_PERMISSION));
	}
	ft_dprintf(2, "here %d\n", fd);
	if (redir->redir_fd != -1)
	{
		//check redir_fd is not already in use
		//if it is, increment it by one until it is not, then dup2
		struct stat buf;
		if (fstat(redir->redir_fd, &buf) != -1)
			(redir->redir_fd)++;
		if (dup2(fd, redir->redir_fd) == -1)
			return (print_error_bool(false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
		r->redir_fd = redir->redir_fd;
	}
	else if (redir->redir_out)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (print_error_bool(false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
	}
	else
		if (dup2(fd, STDIN_FILENO) == -1)
			return (print_error_bool(false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
	if (redir->redir_fd != fd)
		close(fd);
	return (true);
}

bool	handle_redirects(t_ast *node, t_redir **r)
{
	size_t	i;

	if (!node->redirs)
		return (true);
	i = 0;
	while (node->redirs[i])
	{
		r[i] = (t_redir *) ft_memalloc(sizeof(t_redir));
		initialize_redir_struct(r[i]);
		if (node->redirs[i]->aggregation)
		{
			if (!execute_filedes_aggregation(node->redirs[i], r[i]))
				return (false);
		}
		else
		{
			if (!execute_redirection(node->redirs[i], r[i]))
				return (false);
		}
		i++;
	}
	ast_free_redirs(&node);
	return (true);
}
