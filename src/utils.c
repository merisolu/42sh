/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:03:49 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/14 12:43:19 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	size_t	start;
	size_t	length;
	size_t	index;

	load_cursor(state);
	ft_printf("%s%s", tgetstr("cd", NULL), PROMPT);
	index = 0;
	while (index < ft_strlen(state->input))
	{
		input_get_line_properties(state, index, &start, &length);
		if (start != 0)
			ft_putstr(MULTILINE_PROMPT);
		ft_putstrn(state->input + index, length + 1);
		index += length + 1;
		if (index == ft_strlen(state->input))
			ft_putstr(MULTILINE_PROMPT);
	}
	ft_putchar(' ');
	move_cursor_to_saved_position(state);
	rows = ft_min_size_t(
			input_get_row_count(state, ft_strlen(state->input)),
			state->height);
	if (state->input_start_y + rows > state->height)
		state->input_start_y -= (state->input_start_y + rows) - state->height;
}
