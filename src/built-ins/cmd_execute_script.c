/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute_script.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:28:55 by amann             #+#    #+#             */
/*   Updated: 2022/11/30 14:07:17 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	cmd_execute_script(char *const *args, t_state *state)
{
	int		fd;
	char	*line;

	fd = open(*args + 2, O_RDONLY);
	if (fd == -1 || access(*args + 2, X_OK))
		return (print_error(
				1, ETEMPLATE_SHELL_SIMPLE, ERR_NO_PERMISSION));
	ft_get_next_line(fd, &line);
	if (!line)
		return (1);
	ft_strdel(&line);
	state->running_script = true;
	while (ft_get_next_line(fd, &line))
	{
		if (!line)
			return (1);
		ft_strclr(state->input_context.input);
		ft_strcpy(state->input_context.input, line);
		if (ft_strlen(state->input_context.input) > 0)
			tokenize_and_execute(state);
		ft_strdel(&line);
	}
	state->running_script = false;
	close(fd);
	return (0);
}
