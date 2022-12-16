/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_orig_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:08:41 by amann             #+#    #+#             */
/*   Updated: 2022/12/16 17:13:35 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static bool	dup_fd(int fd, int *i)
{
	if (!fd_is_open(fd))
		return (print_error_bool(
				false, "21sh: %i: %s\n", fd, ERR_BAD_FD));
	*i = dup(fd);
	if (*i == -1)
		return (print_error_bool(false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
	return (true);
}

bool	already_duped(t_redir **head, int fd)
{
	int	i;

	i = 0;
	while (head[i])
	{
		if (fd == STDERR_FILENO && (head[i])->saved_err != -1)
			return (true);
		if (fd == STDOUT_FILENO && (head[i])->saved_out != -1)
			return (true);
		if (fd == STDIN_FILENO && (head[i])->saved_in != -1)
			return (true);
		i++;
	}
	return (false);
}

bool	copy_orig_fd(t_ast_redir *redir, t_redir **r, t_redir **head)
{
	if (redir->redir_out)
	{
		if (redir->redir_fd == STDERR_FILENO
			&& !already_duped(head, STDERR_FILENO))
		{
			return (dup_fd(STDERR_FILENO, &((*r)->saved_err)));
		}
		else if (!already_duped(head, STDOUT_FILENO))
			return (dup_fd(STDOUT_FILENO, &((*r)->saved_out)));
	}
	else if (!already_duped(head, STDIN_FILENO))
		return (dup_fd(STDIN_FILENO, &(*r)->saved_in));
	return (true);
}
