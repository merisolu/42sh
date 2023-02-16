/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_save.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:45:48 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/16 14:47:32 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void	history_save(t_state *state)
{
	int		file;
	char	*path;
	int		i;

	path = get_history_file_path();
	if (!path)
		return ;
	file = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (file == -1)
	{
		free(path);
		return ;
	}
	i = HISTORY_SIZE - 1;
	while (ft_strlen(state->history[i]) == 0 && i > 1)
		i--;
	while (i > 0)
	{
		if (write(file, state->history[i], ft_strlen(state->history[i])) == -1
			|| write(file, "\n", 1) == -1)
			break ;
		i--;
	}
	close(file);
	free(path);
}
