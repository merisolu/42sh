/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:18:02 by amann             #+#    #+#             */
/*   Updated: 2022/12/18 20:08:31 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	set_open_flags(t_ast_redir *redir, int *perm)
{
	int	open_flags;

	if (redir->redir_out)
	{
		open_flags = O_WRONLY | O_CREAT;
		if (ft_strequ(redir->redir_op, REDIR_APPEND))
			open_flags |= O_APPEND;
		else
			open_flags |= O_TRUNC;
	}
	else
	{
		open_flags = O_RDONLY;
		*perm = 0450;
	}
	return (open_flags);
}

static int	open_fd(t_ast_redir *redir, int open_flags, int perm)
{
	int	fd;

	fd = open(redir->redir_file, open_flags, perm);
	if (fd == -1)
	{
		if (ft_is_dir(redir->redir_file))
			return (print_error_bool(false, ERRTEMPLATE_NAMED,
					redir->redir_file, ERR_IS_DIR));
		if (access(redir->redir_file, F_OK) == 0)
		{
			return (print_error_bool(
					false, ERRTEMPLATE_NAMED,
					redir->redir_file, ERR_NO_PERMISSION));
		}
		return (print_error_bool(false, ERRTEMPLATE_NAMED,
				redir->redir_file, ERR_NO_PERMISSION));
	}
	return (fd);
}

static bool	set_specified_fd(t_ast_redir *redir, int fd, t_redir *r)
{
	redir->redir_fd_alias = redir->redir_fd;
	if (redir->redir_fd_alias > 2)
	{
		while (fd_is_open(redir->redir_fd_alias) && redir->redir_fd > 2)
			(redir->redir_fd_alias)++;
	}
	if (dup2(fd, redir->redir_fd_alias) == -1)
		return (print_error_bool(
				false, ERRTEMPLATE_SIMPLE, ERR_DUP_FAIL));
	r->redir_fd = redir->redir_fd_alias;
	return (true);
}

static bool	set_redirect_destination(t_ast_redir *redir, int fd)
{
	if (redir->redir_out)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (print_error_bool(
					false, ERRTEMPLATE_SIMPLE, ERR_DUP_FAIL));
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (print_error_bool(
					false, ERRTEMPLATE_SIMPLE, ERR_DUP_FAIL));
	}
	return (true);
}

bool	execute_redirection(t_ast_redir *redir, t_redir *r, t_redir **head)
{
	int			open_flags;
	int			perm;
	int			fd;

	if ((redir->redir_fd == -1 || redir->redir_fd < 3)
		&& !copy_orig_fd(redir, &r, head))
		return (false);
	perm = 0644;
	open_flags = set_open_flags(redir, &perm);
	fd = open_fd(redir, open_flags, perm);
	if (fd == -1)
		return (false);
	if (redir->redir_fd != -1)
	{
		if (!set_specified_fd(redir, fd, r))
			return (false);
	}
	else
	{
		if (!set_redirect_destination(redir, fd))
			return (false);
	}
	if (redir->redir_fd_alias != fd)
		close(fd);
	return (true);
}
