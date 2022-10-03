/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:20:31 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/03 16:14:20 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	history_move_up(t_state *state)
{
	size_t	i;

	i = HISTORY_SIZE - 1;
	while (i > 0)
	{
		ft_strcpy(state->history[i], state->history[i - 1]);
		i--;
	}
	ft_bzero(state->history[0], INPUT_MAX_SIZE);
}

/*
 * Stores *input to state->history[0], as long it's not a duplicate of
 * previous history entry.
 *
 * Attempting to store a duplicate entry is not an error. The function will
 * instead just return 1 without adding the entry to the array.
 *
 * Previous entries are "moved up" one spot before storing the given input. So
 * the string at history[0] is moved to history[1], etc. The entry at
 * history[HISTORY_SIZE - 1] is overwritten.
 *
 * Returns 1 on success, 0 on error.
 */
int	history_store(char *input, t_state *state)
{
	state->history_index = -1;
	if (ft_strequ(state->history[0], input))
		return (1);
	history_move_up(state);
	ft_strcpy(state->history[0], input);
	return (1);
}

/*
 * Copies state->history[state->history_index + diff] to state->input. (Latest
 * command is at index 0).
 *
 * Range is clamped between -1 and HISTORY_SIZE -1.
 * 
 * Returns 1 on success, 0 on error.
 */
int	history_recall(int diff, t_state *state)
{
	int	new_index;

	new_index = ft_clamp(state->history_index + diff, -1, HISTORY_SIZE - 1);
	if (new_index > -1)
	{
		if (state->history[new_index][0] != '\0')
			ft_strcpy(state->input, state->history[new_index]);
		else
			new_index = state->history_index;
	}
	else
		ft_strcpy(state->input, "");
	state->cursor = ft_strlen(state->input);
	state->history_index = new_index;
	return (1);
}
