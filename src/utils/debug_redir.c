/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:00:19 by amann             #+#    #+#             */
/*   Updated: 2022/12/05 14:11:50 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
 * opens a file and appends data from the redir structs for ease of debugging.
 * Printing to the stdout is not always easy when testing redirections.
 */

void	debug_redir(t_ast_redir *redir, t_redir *r)
{
	int	fd;

	fd = open(
			"test",
			O_CREAT | O_RDWR | O_APPEND,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR | S_IROTH
			);
	ft_dprintf(
		fd,
		"agg to :%d\nagg from: %d\n\nfd in: %d\nfd out: %d\
		\nsaved in: %d\nsaved out: %d\nsaved fd:%d\n-----\n\n",
		redir->agg_to,
		redir->agg_from,
		r->fd_in,
		r->fd_out,
		r->saved_in,
		r->saved_out,
		r->saved_fd
		);
	close(fd);
}
