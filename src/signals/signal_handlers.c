/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:57:03 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/20 13:01:40 by jumanner         ###   ########.fr       */
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
	signal(SIGINT, set_signal_int);
	signal(SIGWINCH, set_signal_int);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}

void	reset_signal_handlers(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
}
