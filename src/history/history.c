/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:20:31 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/16 17:50:45 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static void	history_move_down(t_state *state)
{
	size_t	i;

	i = HISTORY_SIZE - 1;
	while (i > 0)
	{
		ft_strcpy(state->history[i], state->history[i - 1]);
		ft_strclr(state->history[i - 1]);
		i--;
	}
	ft_bzero(state->history[0], INPUT_MAX_SIZE);
}

/*
 * Stores *input to state->history[0], as long it's not a duplicate of
 * previous history entry or we are running a script.
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

int	history_store(char *input, t_state *state, int into_temp)
{
	int		target_index;
	size_t	copy_length;

	if (state->running_script)
		return (1);
	if (into_temp)
		target_index = 0;
	else
		target_index = 1;
	state->history_index = 0;
	if (ft_strlen(input) == 0)
		return (1);
	if (ft_strequ(state->history[target_index], input))
		return (1);
	if (!into_temp)
		history_move_down(state);
	ft_strclr(state->history[target_index]);
	copy_length = ft_strlen(input);
	ft_strncpy(state->history[target_index], input, copy_length);
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

	new_index = state->history_index + diff;
	if (new_index < 0 || new_index > HISTORY_SIZE - 1
		|| (new_index != 0 && state->history[new_index][0] == '\0'))
		return (1);
	if (state->history_index == 0 && diff > 0)
		history_store(state->input_context.input, state, 1);
	ft_strclr(state->input_context.input);
	ft_strcpy(state->input_context.input, state->history[new_index]);
	state->input_context.cursor = ft_strlen(state->input_context.input);
	state->history_index = new_index;
	return (1);
}
