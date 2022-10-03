/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:13:18 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/03 17:46:21 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 * Outputs the ANSI escape sequence for requesting the cursor's position.
 *
 * The output is then parsed and saved by parse_cursor().
 */
void	save_cursor(void)
{
	ft_dprintf(STDIN_FILENO, "\x1B[6n");
}

/*
 * Parses the ANSI escape sequence which reports the current cursor's position.
 * The format is: ESC[{ROW};{COLUMN}R.
 *
 * After the output has been parsed, the row and column are stored in *state.
 */
int	parse_cursor(char buf[BUF_SIZE], t_state *state)
{
	size_t	x;
	size_t	y;
	size_t	i;

	if (ft_dstchr(buf, 'R', BUF_SIZE - 1) == BUF_SIZE)
		return (0);
	x = 0;
	y = 0;
	i = 2;
	while (buf[i] != ';')
	{
		y *= 10;
		y += buf[i] - '0';
		i++;
	}
	i++;
	while (buf[i] != 'R')
	{
		x *= 10;
		x += buf[i] - '0';
		i++;
	}
	state->input_start_x = x;
	state->input_start_y = y;
	return (i + 1);
}

/*
 * Restores the cursor to the position saved in *state.
 */
void	load_cursor(t_state *state)
{
	ft_putstr(tgoto(
			tgetstr("cm", NULL),
			state->input_start_x - 1,
			state->input_start_y - 1));
}
