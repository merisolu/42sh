/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:01:54 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/03 13:36:55 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cursor.h"

size_t	cursor_get_column(t_input_context *context, size_t index)
{
	size_t	start;
	size_t	length;

	input_get_line_properties(context, index, &start, &length);
	if (start == 0)
		return (((index - start) + ft_strlen(PROMPT)) % context->width);
	return (((index - start) + ft_strlen(MULTILINE_PROMPT)) % context->width);
}

size_t	cursor_get_row(t_input_context *context, size_t index)
{
	size_t	result;

	result = input_get_row_count(context, index);
	result += context->input_start_y - 1;
	return (result);
}

void	move_cursor_to_saved_position(t_input_context *context)
{
	ft_putstr(
		tgoto(tgetstr("cm", NULL),
			cursor_get_column(context, context->cursor),
			cursor_get_row(context, context->cursor)));
}
