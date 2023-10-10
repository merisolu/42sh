/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:17:10 by jumanner          #+#    #+#             */
/*   Updated: 2023/10/10 15:53:32 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	run_history_expansion(t_state *state)
{
	int	expansion_result;

	expansion_result = history_expand(state);
	if (expansion_result == 1)
	{
		ft_printf("\n%s", state->input_context.input);
		save_cursor(&(state->input_context));
	}
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
		if (!(state->reading_from_stdin))
			ft_putchar('\n');
		clear_input(&(state->input_context));
		return (false);
	}
	if (!run_history_expansion(state))
		return (false);
	if (!(state->reading_from_stdin)
		&& !terminal_apply_config(&(state->orig_conf)))
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE, ERR_TERMIOS_FAIL));
	if (!state->running_command)
	{
		state->input_context.cursor = ft_strlen(state->input_context.input);
		move_cursor_to_saved_position(&(state->input_context));
	}
	return (true);
}
