/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_bg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:36:17 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/09 13:21:25 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	cmd_bg(char *const *args, t_state *state)
{
	t_job	*job;

	job = get_job(args, state);
	if (!job)
		return (1);
	if (job->state == JOB_RUNNING)
		return (print_error(1,
				"42sh: bg: job %i already in background\n", job->id));
	if (job->state == JOB_DONE)
		return (print_error(1, ERRTEMPLATE_NAMED, "bg", ERR_JOB_TERMINATED));
	if (!terminal_apply_config(&(state->orig_conf)))
		return (print_error(1, ERRTEMPLATE_SIMPLE, ERR_TERMIOS_FAIL));
	if (killpg(job->pids[0], SIGCONT) == -1)
		return (print_error(1, ERRTEMPLATE_SIMPLE, ERR_SIGNAL_SEND));
	job->state = JOB_RUNNING;
	return (0);
}
