/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:05:44 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/22 15:29:48 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

static const t_signal_name_dispatch	*get_signal_table(void)
{
	static const t_signal_name_dispatch	dispatch_table[] = {
	{SIGHUP, "Hangup"},
	{SIGQUIT, "Quit"},
	{SIGILL, "Illegal instruction"},
	{SIGTRAP, "Trace/BPT trap"},
	{SIGABRT, "Abort trap"},
	{SIGEMT, "EMT trap"},
	{SIGFPE, "Floating point exception"},
	{SIGKILL, "Killed"},
	{SIGBUS, "Bus error"},
	{SIGSEGV, "Segmentation fault"},
	{SIGSYS, "Bad system call"},
	{SIGALRM, "Alarm clock"},
	{SIGTERM, "Terminated"},
	{SIGXCPU, "Cputime limit exceeded"},
	{SIGVTALRM, "Virtual timer expired"},
	{SIGPROF, "Profiling timer expired"},
	{SIGUSR1, "User defined signal 1"},
	{SIGUSR2, "User defined signal 2"},
	{0, ""}
	};

	return (dispatch_table);
}

void	print_signal(int signal)
{
	size_t							i;
	const t_signal_name_dispatch	*table;

	table = get_signal_table();
	i = 0;
	while (table[i].signal != 0)
	{
		if (table[i].signal == signal)
		{
			ft_printf("%s: %i\n", table[i].name, signal);
			return ;
		}
		i++;
	}
}
