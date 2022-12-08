/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:35:56 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/08 15:35:53 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static void	add_lines_to_history(int file, t_state *state)
{
	char	*line;

	while (ft_get_next_line(file, &line) != 0)
	{
		history_store(line, state, 0);
		free(line);
	}
}

void	history_load(t_state *state)
{
	int		file;
	char	*path;

	path = get_history_file_path();
	if (!path)
		return ;
	if (!ft_is_file(path))
	{
		free(path);
		return ;
	}
	file = open(path, O_RDONLY);
	if (file == -1)
	{
		free(path);
		print_error(0, ERRTEMPLATE_SIMPLE, ERR_CANNOT_OPEN_HISTORY);
		return ;
	}
	add_lines_to_history(file, state);
	close(file);
	free(path);
}
