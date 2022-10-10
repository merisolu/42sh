/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:03:49 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/10 13:28:23 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 * Attempts to get the terminal's size and put the width and height in
 * characters to the given pointers.
 *
 * Returns 1 if successful, zero otherwise.
 */
static int	get_terminal_size(size_t *width, size_t *height)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) == -1)
		return (0);
	*width = size.ws_col;
	*height = size.ws_row;
	return (1);
}

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

static void	move_cursor_to_saved_position(t_state *state, size_t width)
{
	size_t	cursor_rows;
	size_t	text_rows;
	size_t	column;

	column = ((state->input_start_x + state->cursor + ft_strlen(PROMPT) - 1)
			% width);
	cursor_rows = (state->input_start_x + state->cursor + ft_strlen(PROMPT) - 1)
		/ width;
	text_rows = (ft_strlen(state->input) + ft_strlen(PROMPT)
			+ state->input_start_x - 1) / width;
	ft_putstr(tgoto(tgetstr("ch", NULL), 0, column));
	if (text_rows - cursor_rows > 0)
		ft_putstr(tgoto(tgetstr("UP", NULL), 0, text_rows - cursor_rows));
}

/*
 * Redraws the prompt and current input.
 *
 * Redraw process:
 * 		- First the cursor position is moved back to where the start of the
 * 			prompt was printed.
 * 		- Then, the everything from the cursor to the end of the screen is
 * 			erased, and the prompt and the input are printed back on to
 * 			the screen.
 * 		- After that, the cursor is moved to stored cursor position.
 * 		- Finally, input_start_y position is updated (the position that's
 * 			set now will be used the next time move_cursor_to_saved_position
 * 			is called).
 */
void	print_state(t_state *state)
{
	size_t	width;
	size_t	height;
	size_t	rows;

	if (!get_terminal_size(&width, &height))
	{
		print_error(ERR_SIZE_GET_FAIL, 0);
		return ;
	}
	load_cursor(state);
	ft_printf("%s%s%s ", tgetstr("cd", NULL), PROMPT, state->input);
	move_cursor_to_saved_position(state, width);
	rows = (ft_strlen(state->input) + ft_strlen(PROMPT)) / width;
	if (state->input_start_y + rows > height)
		state->input_start_y -= (state->input_start_y + rows) - height;
	if (state->input_start_y > height)
		state->input_start_y = 0;
}
