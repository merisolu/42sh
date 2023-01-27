/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc_editor_read.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:23:36 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/27 15:25:45 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	cmd_fc_read_and_execute_file(t_state *state)
{
	int		fd;
	char	*line;
	char	*last_newline;

	fd = open(FC_EDIT_FILE, O_RDONLY);
	if (fd == -1)
		return (print_error(
				1, ERRTEMPLATE_NAMED, "fc", ERR_OPEN_FAIL));
	while (ft_get_next_line(fd, &line) > 0)
	{
		ft_strclr(state->input_context.input);
		ft_strncpy(state->input_context.input, line, INPUT_MAX_SIZE);
		last_newline = ft_strrchr(state->input_context.input, '\n');
		if (last_newline)
			*last_newline = '\0';
		ft_putstr(state->input_context.input);
		tokenize_and_execute(state);
		free(line);
	}
	return (state->last_return_value);
}
