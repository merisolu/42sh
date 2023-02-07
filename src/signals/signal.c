/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:20:30 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/07 15:39:33 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

extern int	g_last_signal;

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

static void	handle_child(t_state *state)
{
	jobs_check_status(state);
}

static void	handle_hangup(t_state *state)
{
	size_t	i;

	i = 0;
	while (i < MAX_JOBS)
	{
		if (state->jobs[i].state == JOB_STOPPED)
			killpg(state->jobs[i].pids[0], SIGCONT);
		killpg(state->jobs[i].pids[0], SIGHUP);
		i++;
	}
	signal(SIGHUP, SIG_DFL);
	kill(getpid(), SIGHUP);
}

void	check_signal(t_state *state)
{
	if (g_last_signal == SIGCHLD)
		handle_child(state);
	else if (g_last_signal == SIGINT)
		handle_interrupt(state);
	else if (g_last_signal == SIGWINCH)
		handle_size_change(state);
	else if (g_last_signal == SIGHUP)
		handle_hangup(state);
	g_last_signal = 0;
}
