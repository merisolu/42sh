/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:42:30 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/07 11:43:30 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int	g_last_signal;

static void	append_input(t_state *state, char character)
{
	if (ft_strlen(state->input) == INPUT_MAX_SIZE)
	{
		ft_putstr(tgetstr("bl", NULL));
		ft_putstr(tgetstr("vb", NULL));
		return ;
	}
	ft_memmove(state->input + state->cursor + 1, state->input + state->cursor,
		ft_strlen(state->input) - state->cursor);
	state->input[state->cursor] = character;
	state->cursor++;
}

static t_input_result	get_line(t_state *state)
{
	int		read_count;
	char	buf[BUF_SIZE + 1];
	int		i;

	ft_bzero(&buf, BUF_SIZE + 1);
	read_count = read(STDIN_FILENO, &buf, BUF_SIZE);
	if (read_count == 0)
		return (NOTHING_READ);
	i = 0;
	while (i < read_count)
	{
		i += check_movement(buf + i, state);
		if (i >= BUF_SIZE)
			break ;
		if (handle_key(buf + i, state) == NEWLINE_FOUND)
			return (NEWLINE_FOUND);
		else if (ft_isprint(buf[i]))
		{
			append_input(state, buf[i]);
			print_state(state);
		}
		i++;
	}
	return (NO_NEWLINE_FOUND);
}

t_input_result	get_input(t_state *state)
{
	t_input_result	result;

	result = get_line(state);
	if (result == NO_NEWLINE_FOUND)
		print_state(state);
	if (result == NEWLINE_FOUND)
		return (NEWLINE_FOUND);
	else if (result == ERROR)
		return (print_error(ERR_LINE_READ, 1));
	return (result);
}
