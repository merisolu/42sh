/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc_editor_write.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:23:36 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/27 11:57:39 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static bool	write_command_to_fd(int fd, int history_index, t_state *state)
{
	int	write_result;

	write_result = write(fd, state->history[history_index],
			ft_strlen(state->history[history_index]));
	if (write_result == -1)
		return (false);
	write_result = write(fd, "\n", 1);
	return (write_result != -1);
}

bool	cmd_fc_write_commands_to_file(t_fc_range *range, t_state *state)
{
	int		fd;
	bool	write_successful;
	int		i;

	fd = open(FC_EDIT_FILE, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (print_error_bool(
				false, ERRTEMPLATE_NAMED, "fc", ERR_OPEN_FAIL));
	i = range->start;
	while (1)
	{
		write_successful = write_command_to_fd(
				fd, cmd_fc_range_number_to_index(i, state), state);
		if (!write_successful || i == range->end)
			break ;
		if (range->start > range->end)
			i--;
		else
			i++;
	}
	close(fd);
	if (!write_successful)
		print_error(0, ERRTEMPLATE_NAMED, "fc", ERR_WRITE_FAIL);
	return (write_successful);
}
