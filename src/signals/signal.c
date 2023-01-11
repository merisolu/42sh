/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:20:30 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/11 11:33:05 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

extern int	g_last_signal;

static void	set_signal_int(int signal)
{
	g_last_signal = signal;
}

static void	handle_interrupt(t_state *state)
{
	state->input_context.cursor = ft_strlen(state->input_context.input);
	display(&(state->input_context), 1);
	ft_putchar('\n');
	clear_input(&(state->input_context));
	save_cursor(&(state->input_context));
	display(&(state->input_context), 1);
}

static void	handle_size_change(t_state *state)
{
	update_window_size(&(state->input_context));
	display(&(state->input_context), 1);
}

void	set_signal_handling(void)
{
	signal(SIGINT, set_signal_int);
	signal(SIGWINCH, set_signal_int);
	signal(SIGTSTP, set_signal_int);
}

void	check_signal(t_state *state)
{
	if (g_last_signal == SIGINT)
		handle_interrupt(state);
	else if (g_last_signal == SIGWINCH)
		handle_size_change(state);
	g_last_signal = 0;
}
