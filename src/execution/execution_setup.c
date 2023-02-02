/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:17:10 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/02 14:26:53 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	run_history_expansion(t_state *state)
{
	int	expansion_result;

	expansion_result = history_expand(state);
	if (expansion_result == 1)
		ft_printf("\n%s", state->input_context.input);
	else if (expansion_result == -1)
	{
		clear_input(&(state->input_context));
		return (false);
	}
	return (true);
}

bool	execution_setup(t_state *state)
{
	if (ft_strisempty(state->input_context.input))
	{
		ft_putchar('\n');
		clear_input(&(state->input_context));
		return (false);
	}
	if (!run_history_expansion(state))
		return (false);
	if (!terminal_apply_config(&(state->orig_conf)))
	{
		print_error(1, ERRTEMPLATE_SIMPLE, ERR_TERMIOS_FAIL);
		return (false);
	}
	state->input_context.cursor = ft_strlen(state->input_context.input);
	move_cursor_to_saved_position(&(state->input_context));
	ft_putchar('\n');
	return (true);
}
