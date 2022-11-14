/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:28:24 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/14 11:52:58 by jumanner         ###   ########.fr       */
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
		if (start != 0)
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

/*
 * Redraws the prompt and current input.
 *
 * Redraw process:
 * 		- First the cursor position is moved back to where the start of the
 * 			prompt was printed with load_cursor().
 * 		- Then, the everything from the cursor to the end of the screen is
 * 			erased, and the prompt and the input are printed back on to
 * 			the screen.
 * 		- After that, the cursor is moved to stored cursor position.
 * 		- Finally, input_start_y position is updated (the position that's
 * 			set now will be used the next time load_cursor() is called).
 */
void	display(t_input_context *context)
{
	size_t	rows;
	char	*formatted_input;

	load_cursor(context);
	formatted_input = get_formatted_input(context);
	if (formatted_input)
	{
		ft_putstr(formatted_input);
		free(formatted_input);
	}
	else
		ft_printf("%s%s%s", context->start_prompt, tgetstr("cd", NULL),
			ERR_MALLOC_FAIL);
	move_cursor_to_saved_position(context);
	rows = ft_min_size_t(
			input_get_row_count(context, ft_strlen(context->input)
				+ (context->input_start_x - 1)),
			context->height);
	if (context->input_start_y + rows >= context->height)
		context->input_start_y -= (context->input_start_y + rows)
			- context->height;
}
