/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:18:05 by amann             #+#    #+#             */
/*   Updated: 2023/02/22 12:42:34 by jumanner         ###   ########.fr       */
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
}

static bool	redirects_loop(t_ast_redir **ast_head, t_redir **redir_head, int i)
{
	if (ast_head[i]->aggregation)
	{
		if (!execute_filedes_aggregation(&(ast_head[i]),
				redir_head[i], ast_head, redir_head))
			return (false);
	}
	else
	{
		if (!execute_redirection(ast_head[i], redir_head[i], redir_head))
			return (false);
	}
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
		if (ft_strequ(node->redirs[i]->redir_op, REDIR_HEREDOC))
		{
			i++;
			continue ;
		}
		free(r[i]);
		r[i] = (t_redir *) ft_memalloc(sizeof(t_redir));
		if (!r[i])
			return (print_error_bool(false, ERRTEMPLATE_SIMPLE,
					ERR_MALLOC_FAIL));
		initialize_redir_struct(r[i]);
		if (!redirects_loop(node->redirs, r, i))
			return (false);
		i++;
	}
	return (true);
}
