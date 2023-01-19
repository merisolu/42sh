/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_bg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:36:17 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/19 12:37:18 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	cmd_bg(char *const *args, t_state *state)
{
	t_job	*job;

	(void)args;
	if (!state->current_job)
		return (print_error(1, ERRTEMPLATE_DOUBLE_NAMED,
				"bg", "current", ERR_NO_SUCH_JOB));
	job = state->current_job;
	if (!terminal_apply_config(&(state->orig_conf)))
		return (print_error(1, ERRTEMPLATE_SIMPLE, ERR_TERMIOS_FAIL));
	if (killpg(job->pids[0], SIGCONT) == -1)
		return (print_error(1, ERRTEMPLATE_SIMPLE, ERR_SIGNAL_SEND));
	job->state = JOB_RUNNING;
	job_wait(job, false, state);
	return (0);
}
