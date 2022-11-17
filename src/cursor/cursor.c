/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:13:18 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/16 17:57:14 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cursor.h"

/*
 * Parses the ANSI escape sequence which reports the current cursor's position.
 * The format is: ESC[{ROW};{COLUMN}R.
 *
 * After the output has been parsed, the row and column are stored in *state.
 */

static int	parse_cursor(char buf[BUF_SIZE], t_input_context *context)
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
	context->input_start_x = x;
	context->input_start_y = y;
	return (i + 1);
}

/*
 * Outputs the ANSI escape sequence for requesting the cursor's position.
 *
 * The output is then parsed and saved by parse_cursor().
 */

void	save_cursor(t_input_context *context)
{
	char	buf[BUF_SIZE];

	ft_putstr_fd("\x1B[6n", STDIN_FILENO);
	ft_bzero(&buf, BUF_SIZE);
	if (read(STDIN_FILENO, &buf, BUF_SIZE) > 0)
		parse_cursor(buf, context);
}

/*
 * Restores the cursor to the position saved in *state.
 */

void	load_cursor(t_input_context *context)
{
	ft_putstr(tgoto(
			tgetstr("cm", NULL),
			context->input_start_x - 1,
			context->input_start_y - 1));
}
