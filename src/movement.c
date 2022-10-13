/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:58:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/13 12:45:54 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	handle_history(char buf[BUF_SIZE], t_state *state)
{
	if (ft_strnequ(buf, ARROW_UP, ft_strlen(ARROW_UP)))
		history_recall(1, state);
	else if (ft_strnequ(buf, ARROW_DOWN, ft_strlen(ARROW_DOWN)))
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

	start_limit = 0;
	end_limit = ft_strlen(state->input);
	offset = 0;
	if (ft_strnequ(buf, ARROW_LEFT_ALT, ft_strlen(ARROW_LEFT_ALT)))
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
	if (ft_strnequ(buf, ARROW_LEFT, ft_strlen(ARROW_LEFT)))
	{
		if (state->cursor > 0)
			state->cursor--;
		while (state->cursor > 0 && state->input[state->cursor] == '\n')
			state->cursor--;
	}
	else if (ft_strnequ(buf, ARROW_RIGHT, ft_strlen(ARROW_RIGHT)))
	{
		if (state->cursor + 1 <= ft_strlen(state->input))
			state->cursor++;
		while (state->cursor + 1
			<= ft_strlen(state->input) && state->input[state->cursor] == '\n')
			state->cursor++;
	}
	else if (ft_strnequ(buf, HOME_KEY, ft_strlen(HOME_KEY)))
		state->cursor = 0;
	else if (ft_strnequ(buf, END_KEY, ft_strlen(END_KEY)))
		state->cursor = ft_strlen(state->input);
	else
		return (0);
	return (3);
}

static t_movement_handler_dispatch	*get_dispatch_table(void)
{
	static const t_movement_handler_dispatch	dispatch_table[] = {
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

	return ((t_movement_handler_dispatch *)dispatch_table);
}

int	check_movement(char *buf, t_state *state)
{
	size_t						i;
	t_movement_handler_dispatch	*dispatch_table;

	dispatch_table = get_dispatch_table();
	if (buf[0] != 0x1B)
		return (0);
	i = 0;
	while (dispatch_table[i].run != NULL)
	{
		if (ft_strnequ(dispatch_table[i].activator, buf,
				ft_strlen(dispatch_table[i].activator)))
			return (dispatch_table[i].run(buf, state));
		i++;
	}
	return (0);
}
