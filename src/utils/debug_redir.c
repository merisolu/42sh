/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:00:19 by amann             #+#    #+#             */
/*   Updated: 2022/12/16 17:24:13 by amann            ###   ########.fr       */
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

	(void) redir;
	fd = open(
			"test",
			O_CREAT | O_RDWR | O_APPEND,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR | S_IROTH
			);
	ft_dprintf(
		fd,
		"saved in: %d\nsaved out: %d\n\
		saved err: %d\nsaved fd: %d\nfd agg: %d\n-----\n\n",
		r->saved_in,
		r->saved_out,
		r->saved_err,
		r->saved_fd,
		r->fd_agg
		);
	close(fd);
}
