/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:20:30 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/11 10:19:10 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int	g_last_signal;

static void	set_signal_int(int signal)
{
	g_last_signal = signal;
}

static void	handle_interrupt(t_state *state)
{
	clear_input(state, 1);
	save_cursor(state);
	print_state(state);
}

static void	handle_size_change(t_state *state)
{
	update_window_size(state);
	print_state(state);
}

void	set_signal_handling(void)
{
	signal(SIGINT, set_signal_int);
	signal(SIGWINCH, set_signal_int);
}

void	check_signal(t_state *state)
{
	if (g_last_signal == SIGINT)
		handle_interrupt(state);
	else if (g_last_signal == SIGWINCH)
		handle_size_change(state);
	g_last_signal = 0;
}
