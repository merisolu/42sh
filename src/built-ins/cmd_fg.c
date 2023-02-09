/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:11:48 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/09 11:46:22 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	cmd_fg(char *const *args, t_state *state)
{
	t_job	*job;

	job = get_job(args, state);
	if (!job)
		return (1);
	ft_putendl(job->command);
	if (!terminal_apply_config(&(state->orig_conf)))
		return (print_error(1, ERRTEMPLATE_SIMPLE, ERR_TERMIOS_FAIL));
	if (killpg(job->pids[0], SIGCONT) == -1)
		return (print_error(1, ERRTEMPLATE_SIMPLE, ERR_SIGNAL_SEND));
	if (ioctl(STDIN_FILENO, TIOCSPGRP, &(job->pids[0])) == -1)
		return (print_error(1, ERRTEMPLATE_SIMPLE, ERR_FOREGROUND_GROUP));
	job->state = JOB_RUNNING;
	job_wait(job, false, state);
	if (job->state == JOB_DONE)
		job->needs_status_print = false;
	return (0);
}
