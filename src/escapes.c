/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escapes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:58:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/09/20 14:52:16 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	handle_history(char buf[BUF_SIZE], t_state *state)
{
	if (buf[2] == 0x41)
		history_recall(1, state);
	else if (buf[2] == 0x42)
		history_recall(-1, state);
	else
		return (0);
	return (3);
}

static int	handle_cursor(char buf[BUF_SIZE], t_state *state)
{
	if (buf[2] == 0x43 || buf[1] == 0x66)
	{
		if (state->cursor + 1 <= ft_strlen(state->input) + ft_strlen(PROMPT))
			state->cursor++;
	}
	else if (buf[2] == 0x44 || buf[1] == 0x62)
	{
		if (state->cursor - 1 >= ft_strlen(PROMPT))
			state->cursor--;
	}
	else
		return (0);
	return (3 - ((buf[2] == 0x66 || buf[2] == 0x62) * 3));
}

static int	handle_arrows(char buf[BUF_SIZE], t_state *state)
{
	int	return_value;

	return_value = parse_cursor(buf, state);
	if (return_value > 0)
		return (return_value);
	return_value = handle_history(buf, state);
	if (return_value > 0)
		return (return_value);
	return (handle_cursor(buf, state));
}

int	check_escape_sequence(char buf[BUF_SIZE], t_state *state)
{
	size_t									i;
	static const t_input_handler_dispatch	dispatch_table[] = {
	{0x5B, &handle_arrows},
	{0x62, &handle_cursor},
	{0x66, &handle_cursor},
	{0, NULL}
	};

	if (buf[0] != 0x1B)
		return (0);
	i = 0;
	while (dispatch_table[i].run != NULL)
	{
		if (dispatch_table[i].control_char == buf[1])
			return (dispatch_table[i].run(buf, state));
		i++;
	}
	return (0);
}
