/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:42:30 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/05 13:58:43 by jumanner         ###   ########.fr       */
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

static int	get_line(t_state *state)
{
	int		read_count;
	char	buf[BUF_SIZE];
	int		i;

	ft_bzero(&buf, BUF_SIZE);
	read_count = read(STDIN_FILENO, &buf, BUF_SIZE);
	if (read_count == 0)
		return (-2);
	i = check_movement(buf, state);
	while (i < read_count)
	{
		if (handle_char(buf, state) == 1)
			return (1);
		if (buf[i] == '\t')
			autocomplete(state);
		else if (buf[i] == CTRL_D)
			return (ctrl_d(state));
		else if (ft_isprint(buf[i]))
			append_input(state, buf[i]);
		i++;
	}
	return (0);
}

int	get_input(t_state *state)
{
	int	result;

	result = get_line(state);
	if (result == 0)
		print_state(state);
	if (result == 1)
		return (1);
	else if (result == -1)
		return (print_error(ERR_LINE_READ, 1));
	return (result);
}
