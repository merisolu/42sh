/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute_script.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:28:55 by amann             #+#    #+#             */
/*   Updated: 2022/11/14 16:40:09 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	cmd_execute_script(char *const *args, t_state *state)
{
	int		fd;
	char	*line;

	fd = open(*args + 2, O_RDONLY);
	if (fd == -1)
		return (print_error(ERR_OPEN_FAIL, 1));
	ft_get_next_line(fd, &line);
	if (!line)
		return (1);
	ft_strdel(&line);
	state->running_script = TRUE;
	while (ft_get_next_line(fd, &line))
	{
		if (!line)
			return (1);
		ft_strclr(state->input_context.input);
		ft_strcpy(state->input_context.input, line);
		tokenize_and_execute(state);
		ft_strdel(&line);
	}
	state->running_script = FALSE;
	close(fd);
	return (0);
}
