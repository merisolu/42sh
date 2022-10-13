/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:01:54 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/13 15:09:01 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static size_t	cursor_get_column(t_state *state, size_t index)
{
	size_t	length;
	size_t	start;

	input_get_line_properties(state, index, &start, &length);
	return (((index - start) + ft_strlen(PROMPT)) % state->width);
}

static size_t	cursor_get_row(t_state *state, size_t index)
{
	size_t	result;

	result = input_get_row_count(state, index + ft_strlen(PROMPT));
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
