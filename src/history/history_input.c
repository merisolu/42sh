/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:41:36 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/01 13:39:47 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

/*
 * Runs any history related reserved input sequence checks. Returns true if
 * the shell should act like a newline was entered. False otherwise.
 */
bool	check_history_reserved_sequences(t_state *state)
{
	if (ft_strequ(ARROW_UP, state->input_context.found_reserved_sequence))
		history_recall(1, state);
	if (ft_strequ(ARROW_DOWN, state->input_context.found_reserved_sequence))
		history_recall(-1, state);
	if (ft_strequ(CTRL_R, state->input_context.found_reserved_sequence))
		return (history_search(state));
	return (false);
}
