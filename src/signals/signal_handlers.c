/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:57:03 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/08 12:47:30 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

extern int	g_last_signal;

static void	set_signal_int(int signal)
{
	g_last_signal = signal;
}

void	set_signal_handling(void)
{
	struct sigaction	new_action;

	new_action.sa_flags = 0;
	new_action.sa_mask = 0;
	new_action.sa_handler = set_signal_int;
	sigaction(SIGHUP, &new_action, NULL);
	signal(SIGINT, set_signal_int);
	signal(SIGWINCH, set_signal_int);
	signal(SIGCHLD, set_signal_int);
	signal(SIGCONT, set_signal_int);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

void	reset_signal_handlers(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGHUP, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGCONT, SIG_DFL);
}
