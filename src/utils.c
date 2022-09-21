/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:03:49 by jumanner          #+#    #+#             */
/*   Updated: 2022/09/21 11:31:48 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 * Attempts to get the terminal's size and put the width and length in
 * characters to the given pointers.
 *
 * Returns 1 if successful, zero otherwise.
 */
static int	get_terminal_size(size_t *width, size_t *length)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) == -1)
		return (0);
	*width = size.ws_col;
	*length = size.ws_row;
	return (1);
}

void	*var_copy(void *var)
{
	return ((void *)ft_strdup((const char *)var));
}

void	clear_input(t_state *state, int newline)
{
	ft_strdel(&(state->input));
	state->cursor = ft_strlen(PROMPT);
	if (newline)
		ft_putchar('\n');
}

static void	move_cursor_to_saved_position(t_state *state, size_t width)
{
	size_t	cursor_rows;
	size_t	text_rows;
	size_t	column;

	column = ((state->input_start_x + state->cursor - 1) % width);
	cursor_rows = (state->input_start_x + state->cursor - 1) / width;
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
 * 			erased (this doesn't move the cursor).
 * 		- After that, the prompt and the input are printed back on to
 * 			the screen.
 * 		- Finally, the cursor is moved to stored cursor position.
 */
void	print_state(t_state *state, int newline)
{
	size_t	width;
	size_t	length;
	size_t	rows;

	if (!get_terminal_size(&width, &length))
	{
		print_error(ERR_SIZE_GET_FAIL, 0);
		return ;
	}
	if (state->input)
	{
		rows = (state->prev_input_len + state->input_start_x - 2) / width;
		if (state->input_start_y + rows + newline > length + 1)
			state->input_start_y -= (state->input_start_y + rows + newline) \
				- length - 1;
		if (state->input_start_y > length)
			state->input_start_y = 0;
		load_cursor(state);
		ft_printf("%s%s%s ", tgetstr("cd", NULL), PROMPT, state->input);
		move_cursor_to_saved_position(state, width);
	}
	else if (!newline)
		ft_putstr(PROMPT);
	state->prev_input_len = ft_strlen(PROMPT) + ft_strlen(state->input) + 1;
}
