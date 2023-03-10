/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:20:30 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/08 12:59:01 by jumanner         ###   ########.fr       */
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

static void	handle_continue(t_state *state)
{
	if (!terminal_apply_config(&(state->input_conf)))
		print_error(1, ERRTEMPLATE_SIMPLE, ERR_TERMIOS_FAIL);
	display(&(state->input_context), 1);
}

void	check_signal(t_state *state)
{
	if (g_last_signal == SIGCHLD)
		jobs_check_status(state);
	else if (g_last_signal == SIGINT)
		handle_interrupt(state);
	else if (g_last_signal == SIGWINCH)
		handle_size_change(state);
	else if (g_last_signal == SIGHUP)
		handle_hangup(state);
	else if (g_last_signal == SIGCONT)
		handle_continue(state);
	g_last_signal = 0;
}
