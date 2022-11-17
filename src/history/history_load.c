/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:35:56 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/17 12:42:23 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void	history_load(t_state *state)
{
	int		file;
	char	*path;
	char	*line;
	int		i;

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
		print_error(ERR_CANNOT_OPEN_HISTORY, 0);
		return ;
	}
	i = 0;
	while (ft_get_next_line(file, &line) != 0)
		history_store(line, state, 0);
	close(file);
	free(path);
}
