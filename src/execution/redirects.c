/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:18:05 by amann             #+#    #+#             */
/*   Updated: 2022/12/18 17:07:53 by amann            ###   ########.fr       */
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
			if (!execute_filedes_aggregation(
					&(node->redirs[i]), r[i], node->redirs, r))
				return (false);
		}
		else
		{
			if (!execute_redirection(node->redirs[i], r[i], r))
				return (false);
		}
		i++;
	}
	ast_free_redirs(&node);
	return (true);
}
