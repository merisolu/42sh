/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:01:54 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/21 15:14:33 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cursor.h"

size_t	cursor_get_column(t_input_context *context, size_t index)
{
	size_t	start;
	size_t	length;
	int		newline;

	newline = 0;
	if (index > 0)
	{
		newline = (context->input[index] == '\n');
		index -= newline;
	}
	input_get_line_properties(context, index, &start, &length);
	if (start == 0)
		return (((index - start) + ft_strlen(context->start_prompt)
				+ (context->input_start_x - 1) + newline) % context->width);
	if (length == 0)
		newline = 0;
	return (((index - start) + ft_strlen(context->multiline_prompt) + newline)
		% context->width);
}

size_t	cursor_get_row(t_input_context *context, size_t index)
{
	size_t	result;

	result = input_get_row_count(context, index + (context->input_start_x - 1));
	result -= (context->input[index] == '\n');
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
