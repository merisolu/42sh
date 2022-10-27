/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:01:54 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/18 15:21:54 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t	cursor_get_column(t_state *state, size_t index)
{
	size_t	start;
	size_t	length;

	input_get_line_properties(state, index, &start, &length);
	if (start == 0)
		return (((index - start) + ft_strlen(PROMPT)) % state->width);
	return (((index - start) + ft_strlen(MULTILINE_PROMPT)) % state->width);
}

size_t	cursor_get_row(t_state *state, size_t index)
{
	size_t	result;

	result = input_get_row_count(state, index);
	result += state->input_start_y - 1;
	return (result);
}

void	move_cursor_to_saved_position(t_state *state)
{
	ft_putstr(
		tgoto(tgetstr("cm", NULL),
			cursor_get_column(state, state->cursor),
			cursor_get_row(state, state->cursor)));
}
