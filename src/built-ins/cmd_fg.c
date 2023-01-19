/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:11:48 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/19 12:37:23 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	cmd_fg(char *const *args, t_state *state)
{
	t_job	*job;

	(void)args;
	if (!state->current_job)
		return (print_error(1, ERRTEMPLATE_DOUBLE_NAMED,
				"fg", "current", ERR_NO_SUCH_JOB));
	job = state->current_job;
	if (!terminal_apply_config(&(state->orig_conf)))
		return (print_error(1, ERRTEMPLATE_SIMPLE, ERR_TERMIOS_FAIL));
	if (killpg(job->pids[0], SIGCONT) == -1)
		return (print_error(1, ERRTEMPLATE_SIMPLE, ERR_SIGNAL_SEND));
	if (ioctl(STDIN_FILENO, TIOCSPGRP, &(job->pids[0])) == -1)
		return (print_error(1, ERRTEMPLATE_SIMPLE, ERR_FOREGROUND_GROUP));
	job->state = JOB_RUNNING;
	job_wait(job, false, state);
	return (0);
}
