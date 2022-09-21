/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escapes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:58:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/09/21 11:43:03 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	handle_history(char buf[BUF_SIZE], t_state *state)
{
	if (ft_strequ(buf, ARROW_UP))
		history_recall(1, state);
	else if (ft_strequ(buf, ARROW_DOWN))
		history_recall(-1, state);
	else
		return (0);
	return (3);
}

static int	handle_cursor(char buf[BUF_SIZE], t_state *state)
{
	if (ft_strequ(buf, ARROW_LEFT))
	{
		if (state->cursor - 1 >= ft_strlen(PROMPT))
			state->cursor--;
	}
	else if (ft_strequ(buf, ARROW_RIGHT))
	{
		if (state->cursor + 1 <= ft_strlen(state->input) + ft_strlen(PROMPT))
			state->cursor++;
	}
	else
		return (0);
	return (3);
}

int	check_escape_sequence(char buf[BUF_SIZE], t_state *state)
{
	size_t									i;
	size_t									cursor_parse_result;
	static const t_input_handler_dispatch	dispatch_table[] = {
	{ARROW_UP, &handle_history},
	{ARROW_DOWN, &handle_history},
	{ARROW_LEFT, &handle_cursor},
	{ARROW_RIGHT, &handle_cursor},
	{0, NULL}
	};

	if (buf[0] != 0x1B)
		return (0);
	cursor_parse_result = parse_cursor(buf, state);
	if (cursor_parse_result > 0)
		return (cursor_parse_result);
	i = 0;
	while (dispatch_table[i].run != NULL)
	{
		if (ft_strequ(dispatch_table[i].activator, buf))
			return (dispatch_table[i].run(buf, state));
		i++;
	}
	return (0);
}
