/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:04:07 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/03 13:07:02 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// TODO: Redo comment
/*
 * Returns the properties of a line of text contained in state->input at
 * the given index.
 *
 * The values returned will indicate a line that either:
 * 		- Starts from the beginning of state->input and ends at '/0'.
 * 		- Starts from the beginning of state->input and ends in a '\n'.
 * 		- Starts and ends in a '\n'.
 * 		- Starts from a '\n' and ends at '/0'.
 *
 * The function sets the start index and the length of the line to *start and
 * *length respectively.
 */
void	input_get_line_properties(\
	t_input_context *state, size_t index, size_t *start, size_t *length)
{
	size_t	section_start;
	size_t	section_end;

	section_start = index;
	while (section_start > 0)
	{
		if (state->input[section_start] == '\n')
		{
			if (section_start < index)
				section_start++;
			break ;
		}
		section_start--;
	}
	section_end = ft_dstchr(state->input + section_start, '\n',
			ft_strlen(state->input));
	if (section_end == ft_strlen(state->input) + 1)
			section_end = ft_strlen(state->input);
	section_end += section_start;
	if (length)
		*length = section_end - section_start;
	if (start)
		*start = section_start;
}

// TODO: Redo comment
/*
 * Returns the amount of rows state->input takes up in the terminal window,
 * starting from the given index. Manually entered newlines and line wrap
 * are both counted.
 */
size_t	input_get_row_count(t_input_context *context, size_t index)
{
	size_t	result;
	size_t	start;
	size_t	length;

	input_get_line_properties(context, index, &start, &length);
	result = ft_strchrrcount(context->input, '\n', index);
	while (index > 0)
	{
		if (start == 0)
		{
			result += ((index - start) + ft_strlen(PROMPT)) / context->width;
			break ;
		}
		else
			result += ((index - start) + ft_strlen(MULTILINE_PROMPT))
				/ context->width;
		index = start - 1;
		input_get_line_properties(context, index, &start, &length);
	}
	return (result);
}
