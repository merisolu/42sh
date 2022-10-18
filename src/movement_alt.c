/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_alt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:40:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/18 16:44:32 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	handle_alt_left_right(char buf[BUF_SIZE], t_state *state)
{
	size_t	start_limit;
	size_t	offset;
	size_t	end_limit;
	int		delta;

	start_limit = 0;
	end_limit = ft_strlen(state->input);
	offset = 0;
	if (ft_strnequ(buf, ARROW_LEFT_ALT, ft_strlen(ARROW_LEFT_ALT)))
	{
		offset++;
		delta = -1;
	}
	else
		delta = 1;
	while (state->cursor + delta >= start_limit
		&& state->cursor + delta < end_limit
		&& !ft_isalnum(state->input[state->cursor - offset]))
		state->cursor += delta;
	while (state->cursor + delta >= start_limit
		&& ft_isalnum(state->input[state->cursor - offset]))
		state->cursor += delta;
	return (3);
}

int	handle_alt_up_down(char buf[BUF_SIZE], t_state *state)
{
	size_t	column;
	size_t	start;
	size_t	length;

	column = cursor_get_column(state, state->cursor);
	if (ft_strnequ(buf, ARROW_UP_ALT, ft_strlen(ARROW_UP_ALT)))
	{
		while (state->cursor > 0 && state->input[state->cursor] != '\n')
			state->cursor--;
		if (state->cursor > 0)
			state->cursor--;
		input_get_line_properties(state, state->cursor, &start, &length);
		if (state->cursor < length - column + 1)
			return (6);
		state->cursor -= length - column + 1;
	}
	else if (ft_strnequ(buf, ARROW_DOWN_ALT, ft_strlen(ARROW_DOWN_ALT)))
	{
		while (state->cursor < ft_strlen(state->input) - 1 && state->input[state->cursor] != '\n')
			state->cursor++;
		if (state->cursor < ft_strlen(state->input))
			state->cursor++;
		input_get_line_properties(state, state->cursor, &start, &length);
		if (state->cursor + ft_min(column - 2, length - 1) >= ft_strlen(state->input) - 1)
			return (6);
		state->cursor += ft_min(column - 2, length - 1);
	}
	else
		return (0);
	return (6);
}
