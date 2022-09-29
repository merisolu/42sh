/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:58:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/09/29 11:21:02 by jumanner         ###   ########.fr       */
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

static int	handle_alt_arrows(char buf[BUF_SIZE], t_state *state)
{
	size_t	start_limit;
	size_t	offset;
	size_t	end_limit;
	int		delta;

	start_limit = ft_strlen(PROMPT);
	end_limit = ft_strlen(state->input) + ft_strlen(PROMPT);
	offset = ft_strlen(PROMPT);
	if (ft_strequ(buf, ARROW_LEFT_ALT))
	{
		offset++;
		delta = -1;
	}
	else
		delta = 1;
	while (state->cursor + delta >= start_limit
		&& state->cursor + delta < end_limit
		&& !ft_isalnum(state->input[state->cursor - offset]))
		state->cursor += delta;
	while (state->cursor + delta >= start_limit
		&& ft_isalnum(state->input[state->cursor - offset]))
		state->cursor += delta;
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
	else if (ft_strequ(buf, HOME_KEY))
		state->cursor = ft_strlen(PROMPT);
	else if (ft_strequ(buf, END_KEY))
		state->cursor = ft_strlen(state->input) + ft_strlen(PROMPT);
	else
		return (0);
	return (3);
}

static t_input_handler_dispatch	*get_dispatch_table(void)
{
	static const t_input_handler_dispatch	dispatch_table[] = {
	{ARROW_UP, &handle_history},
	{ARROW_DOWN, &handle_history},
	{ARROW_LEFT, &handle_cursor},
	{ARROW_RIGHT, &handle_cursor},
	{HOME_KEY, &handle_cursor},
	{END_KEY, &handle_cursor},
	{ARROW_LEFT_ALT, &handle_alt_arrows},
	{ARROW_RIGHT_ALT, &handle_alt_arrows},
	{0, NULL}
	};

	return ((t_input_handler_dispatch *)dispatch_table);
}

int	check_movement(char buf[BUF_SIZE], t_state *state)
{
	size_t						i;
	size_t						cursor_parse_result;
	t_input_handler_dispatch	*dispatch_table;

	dispatch_table = get_dispatch_table();
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
