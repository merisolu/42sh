/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:18:05 by amann             #+#    #+#             */
/*   Updated: 2022/12/05 14:12:53 by amann            ###   ########.fr       */
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

static bool	redirect_input(t_ast_redir *redir_node, t_redir *r)
{
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
	if (r->saved_in == -1)
		r->saved_in = dup(STDIN_FILENO);
	if (r->saved_in == -1)
		return (print_error_bool(
				false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
	if (dup2(r->fd_in, STDIN_FILENO) == -1)
		return (print_error_bool(
				false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
	close(r->fd_in);
	r->fd_in = -1;
	return (true);
}

static bool	redirect_output(t_ast_redir *redir, t_redir *r)
{
	int			append;
	static int	perms;

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
	if (r->saved_out == -1)
		r->saved_out = dup(STDOUT_FILENO);
	if (r->saved_out == -1)
		return (print_error_bool(false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
	if (dup2(r->fd_out, STDOUT_FILENO) == -1)
		return (print_error_bool(false, ETEMPLATE_SHELL_SIMPLE, ERR_DUP_FAIL));
	close(r->fd_out);
	r->fd_out = -1;
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
		if (node->redirs[i]->out_type
			&& !redirect_output(node->redirs[i], r))
			return (false);
		if (node->redirs[i]->in_type
			&& !ft_strequ(node->redirs[i]->in_type, REDIR_HEREDOC)
			&& !redirect_input(node->redirs[i], r))
			return (false);
		if (node->redirs[i]->aggregation
			&& !execute_filedes_aggregation(node->redirs[i], r))
			return (false);
		i++;
	}
	return (true);
}
