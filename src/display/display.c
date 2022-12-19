/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:28:24 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/19 15:29:08 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

/*
 * Returns the currently stored input in a form that can be printed to
 * the screen (has prompts, etc).
 */

static char	*get_formatted_input(t_input_context *context)
{
	size_t	start;
	size_t	length;
	size_t	index;
	char	*result;

	result = ft_strjoin(tgetstr("cd", NULL), context->start_prompt);
	index = 0;
	while (result && index < ft_strlen(context->input))
	{
		input_get_line_properties(context, index, &start, &length);
		if (start != 0 && (length > 0
				|| (length == 0 && context->input[index - 1] == '\n')))
			result = ft_strjoinfree(result, context->multiline_prompt);
		if (!result)
			break ;
		result = ft_strnjoinfree(result, context->input + index, length + 1);
		if (!result)
			break ;
		index += length + 1;
		if (index == ft_strlen(context->input))
			result = ft_strjoinfree(result, context->multiline_prompt);
	}
	if (result)
		result = ft_strjoinfree(result, " ");
	return (result);
}

size_t	get_trim_offset(t_input_context *context, char *formatted_input)
{
	size_t	newline_count;
	size_t	result;
	size_t	temp;

	newline_count = ft_strchrcount(formatted_input, '\n');
	result = 0;
	while (newline_count >= context->height)
	{
		temp = ft_dstchr(formatted_input + result, '\n',
				ft_strlen(formatted_input + result));
		result += temp;
		result++;
		newline_count = ft_strchrcount(formatted_input + result, '\n');
	}
	return (result);
}

void	draw(t_input_context *context, int force)
{
	char	*formatted_input;
	size_t	trim;

	formatted_input = get_formatted_input(context);
	if (formatted_input)
	{
		trim = get_trim_offset(context, formatted_input);
		if (force || context->last_displayed_length
			!= ft_strlen(formatted_input + trim))
		{
			load_cursor(context);
			if (trim > 0)
				ft_putstr(tgetstr("cd", NULL));
			ft_putstr(formatted_input + trim);
		}
		context->last_displayed_length = ft_strlen(formatted_input + trim);
		free(formatted_input);
	}
	else
	{
		load_cursor(context);
		ft_printf("%s%s%s", context->start_prompt, tgetstr("cd", NULL),
			ERR_MALLOC_FAIL);
		context->last_displayed_length = 0;
	}
}

/*
 * Redraws the prompt and current input.
 *
 * Redraw process:
 *		- First the cursor position is moved back to where the start of the
 *			prompt was printed with load_cursor().
 *		- Then, the everything from the cursor to the end of the screen is
 *			erased, and the prompt and the input are printed back on to
 *			the screen.
 *		- After that, the cursor is moved to stored cursor position.
 *		- Finally, input_start_y position is updated (the position that's
 *			set now will be used the next time load_cursor() is called).
 */

void	display(t_input_context *context, int force)
{
	size_t	rows;

	draw(context, force);
	rows = ft_min_size_t(
			input_get_row_count(context, ft_strlen(context->input)
				+ (context->input_start_x - 1)),
			context->height);
	if (context->input_start_y + rows >= context->height)
		context->input_start_y -= (context->input_start_y + rows)
			- context->height;
	move_cursor_to_saved_position(context);
}
