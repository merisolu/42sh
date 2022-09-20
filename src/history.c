/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:20:31 by jumanner          #+#    #+#             */
/*   Updated: 2022/09/20 14:52:16 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	swap_input(char *new_input, t_state *state)
{
	free(state->input);
	state->input = ft_strdup(new_input);
	return (state->input != NULL);
}

static void	history_move_up(t_state *state)
{
	size_t	i;

	i = HISTORY_SIZE - 1;
	free(state->history[i]);
	while (i > 0)
	{
		state->history[i] = state->history[i - 1];
		i--;
	}
	state->history[0] = NULL;
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
 * history[HISTORY_SIZE - 1] is freed and discarded.
 *
 * Returns 1 on success, 0 on error.
 */
int	history_store(char *input, t_state *state)
{
	if (!state || !input)
		return (0);
	state->history_index = -1;
	if (ft_strequ(state->history[0], input))
		return (1);
	history_move_up(state);
	state->history[0] = ft_strdup(input);
	return (state->history[0] != NULL);
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
		if (state->history[new_index])
		{
			if (!swap_input(state->history[new_index], state))
				return (print_error(ERR_HISTORY_RECALL, 0));
		}
		else
			new_index = state->history_index;
	}
	else if (!swap_input("", state))
		return (print_error(ERR_HISTORY_RECALL, 0));
	state->cursor = ft_strlen(PROMPT) + ft_strlen(state->input);
	state->history_index = new_index;
	return (1);
}
