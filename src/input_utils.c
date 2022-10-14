/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:53:40 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/14 12:34:37 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	t_state *state, size_t index, size_t *start, size_t *length)
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

/*
 * Returns the amount of rows state->input takes up in the terminal window,
 * starting from the given index. Manually entered newlines and line wrap
 * are both counted.
 */
size_t	input_get_row_count(t_state *state, size_t index)
{
	size_t	result;
	size_t	start;
	size_t	length;

	input_get_line_properties(state, index, &start, &length);
	result = ft_strchrrcount(state->input, '\n', index);
	while (index > 0)
	{
		if (start == 0)
		{
			result += ((index - start) + ft_strlen(PROMPT)) / state->width;
			break ;
		}
		else
			result += ((index - start) + ft_strlen(MULTILINE_PROMPT))
				/ state->width;
		index = start - 1;
		input_get_line_properties(state, index, &start, &length);
	}
	return (result);
}
