/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc_editor_read.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:23:36 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/27 11:58:58 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

// TODO: Read multiple commands.
bool	cmd_fc_read_command_from_file(t_state *state)
{
	int		fd;
	int		read_return;
	char	*last_newline;

	ft_bzero(state->history[1], INPUT_MAX_SIZE);
	fd = open(FC_EDIT_FILE, O_RDONLY);
	if (fd == -1)
		return (print_error_bool(
				false, ERRTEMPLATE_NAMED, "fc", ERR_OPEN_FAIL));
	read_return = read(fd, state->history[1], INPUT_MAX_SIZE);
	if (read_return == -1)
		return (print_error_bool(false, ERRTEMPLATE_NAMED "fc", ERR_READ_FAIL));
	last_newline = ft_strrchr(state->history[1], '\n');
	if (last_newline)
		*last_newline = '\0';
	return (true);
}
