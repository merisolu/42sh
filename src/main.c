/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:35 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/23 11:47:33 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	g_last_signal;

static void	finish_execution(t_state *state)
{
	if (g_last_signal != 0 && state->last_return_value > 128)
		ft_putchar('\n');
	jobs_print_changed(state);
	save_cursor(&(state->input_context));
	display(&(state->input_context), 1);
	jobs_cleanup_finished(state);
}

static t_input_result	input_handler(t_state *state)
{
	t_input_result	result;
	static bool		tab;

	result = get_input(&(state->input_context));
	if (result == INPUT_CALLED_FOR_EXIT)
	{
		state->exiting = 1;
		state->exit_return_value = RETURN_CTRL_D;
	}
	if (result == INPUT_FOUND_RESERVED_SEQUENCE)
	{
		if (ft_strequ(ARROW_UP, state->input_context.found_reserved_sequence))
			history_recall(1, state);
		if (ft_strequ(ARROW_DOWN, state->input_context.found_reserved_sequence))
			history_recall(-1, state);
		if (ft_strequ(TAB, state->input_context.found_reserved_sequence))
		{
			if (autocomplete(state, tab) == 0)
				tab = true;
		}
		display(&(state->input_context), 1);
	}
	else if (result != INPUT_NOTHING_READ)
		tab = false;
	return (result);
}

int	main(const int argc, const char **argv, char *const *env)
{
	t_state	state;

	(void)argc;
	(void)argv;
	if (!setup(&env, &state))
		return (cleanup(&state, 1));
	while (!state.exiting)
	{
		check_signal(&state);
		if (input_handler(&state) == INPUT_MARK_FOUND)
		{
			tokenize_and_execute(&state);
			if (!state.exiting)
				finish_execution(&state);
			g_last_signal = 0;
		}
	}
	history_save(&state);
	ft_putendl("exit");
	return (cleanup(&state, state.exit_return_value));
}
