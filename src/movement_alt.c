/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_alt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:40:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/18 18:14:46 by jumanner         ###   ########.fr       */
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

int	handle_alt_up(char buf[BUF_SIZE], t_state *state)
{
	size_t	column;
	size_t	length;
	size_t	distance;

	(void)buf;
	column = cursor_get_column(state, state->cursor);
	distance = ft_dstrchr(state->input, '\n', state->cursor);
	if (distance != state->cursor + 1)
		state->cursor = state->cursor - (distance + 1);
	else
		state->cursor = 0;
	input_get_line_properties(state, state->cursor, NULL, &length);
	if (state->cursor >= length - column + 1)
		state->cursor -= length - column + 1;
	return (6);
}

int	handle_alt_down(char buf[BUF_SIZE], t_state *state)
{
	size_t	column;
	size_t	length;
	size_t	distance;

	(void)buf;
	column = cursor_get_column(state, state->cursor);
	distance = ft_dstchr(
			state->input + state->cursor,
			'\n',
			ft_strlen(state->input + state->cursor));
	if (distance != ft_strlen(state->input + state->cursor) + 1)
		state->cursor += distance + 1;
	else
		state->cursor = ft_strlen(state->input);
	input_get_line_properties(state, state->cursor, NULL, &length);
	if (state->cursor + ft_min(column - 2, length - 1)
		< ft_strlen(state->input) - 1)
		state->cursor += ft_min(column - 2, length - 1);
	return (6);
}
