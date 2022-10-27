/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:03:49 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 13:11:08 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

void	*var_copy(void *var)
{
	return ((void *)ft_strdup((const char *)var));
}

void	clear_input(t_state *state, int newline)
{
	ft_bzero(state->input, INPUT_MAX_SIZE);
	state->cursor = 0;
	if (newline)
		ft_putchar('\n');
}

void	update_window_size(t_state *state)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) == -1)
		return ;
	state->width = size.ws_col;
	state->height = size.ws_row;
}

/*
 * Returns the currently stored input in a form that can be printed to
 * the screen (has prompts, etc).
 */
static char	*get_formatted_input(t_state *state)
{
	size_t	start;
	size_t	length;
	size_t	index;
	char	*result;

	result = ft_strjoin(tgetstr("cd", NULL), PROMPT);
	index = 0;
	while (result && index < ft_strlen(state->input))
	{
		input_get_line_properties(state, index, &start, &length);
		if (start != 0)
			result = ft_strjoinfree(result, MULTILINE_PROMPT);
		if (!result)
			break ;
		result = ft_strnjoinfree(result, state->input + index, length + 1);
		if (!result)
			break ;
		index += length + 1;
		if (index == ft_strlen(state->input))
			result = ft_strjoinfree(result, MULTILINE_PROMPT);
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
void	print_state(t_state *state)
{
	size_t	rows;
	char	*formatted_input;

	load_cursor(state);
	formatted_input = get_formatted_input(state);
	if (formatted_input)
	{
		ft_putstr(formatted_input);
		free(formatted_input);
	}
	else
		ft_printf("%s%s%s", PROMPT, tgetstr("cd", NULL), ERR_MALLOC_FAIL);
	move_cursor_to_saved_position(state);
	rows = ft_min_size_t(
			input_get_row_count(state, ft_strlen(state->input)),
			state->height);
	if (state->input_start_y + rows > state->height)
		state->input_start_y -= (state->input_start_y + rows) - state->height;
}
