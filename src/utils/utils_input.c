/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:04:07 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/09 14:25:23 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
 * Returns the properties of a line of text contained in context->input at
 * the given index.
 *
 * The values returned will indicate a line that either:
 *		- Starts from the beginning of context->input and ends at '/0'.
 *		- Starts from the beginning of context->input and ends in a '\n'.
 *		- Starts and ends in a '\n'.
 *		- Starts from a '\n' and ends at '/0'.
 *
 * The function sets the start index and the length of the line to *start and
 * *length respectively.
 */

static void	ret_zero(size_t *start, size_t *length)
{
	*start = 0;
	*length = 0;
}

static void	iglp_helper(size_t *start, size_t *length, size_t ss, size_t se)
{
	if (length)
		*length = se;
	if (start)
		*start = ss;
}

void	input_get_line_properties(\
	t_input_context *context, size_t index, size_t *start, size_t *length)
{
	size_t	section_start;
	size_t	section_end;

	if (ft_strlen(context->input) < index)
		return (ret_zero(start, length));
	section_start = index;
	while (section_start > 0)
	{
		if (context->input[section_start] == '\n')
		{
			if (section_start < index)
				section_start++;
			break ;
		}
		section_start--;
	}
	section_end = ft_dstchr(context->input + section_start, '\n',
			ft_strlen(context->input));
	if (section_end == ft_strlen(context->input) + 1)
		section_end = ft_strlen(context->input);
	if (section_start == 0 && section_end == 0 && index > 0)
		section_start = index;
	iglp_helper(start, length, section_start, section_end);
}

/*
 * Returns the amount of rows context->input takes up in the terminal window,
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
			result += ((index - start) + ft_strlen(context->start_prompt))
				/ context->width;
			break ;
		}
		else
			result += ((index - start) + ft_strlen(context->multiline_prompt))
				/ context->width;
		index = start - 1;
		input_get_line_properties(context, index, &start, &length);
	}
	return (result);
}
