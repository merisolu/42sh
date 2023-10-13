/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:39:28 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/23 15:01:16 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

pid_t	job_get_last_pid(t_job *job)
{
	int	i;

	i = MAX_PIDS - 1;
	while (i >= 0)
	{
		if (job->pids[i] != 0)
			return (job->pids[i]);
		i--;
	}
	return (0);
}

void	job_current_update(t_job *new_current, t_state *state)
{
	if (new_current == state->current_job)
		return ;
	state->previous_job = state->current_job;
	state->current_job = new_current;
}

void	job_execute(t_job *job, bool background, t_state *state)
{
	job->needs_status_print = background;
	if (!background)
	{
		job_wait(job, false, state);
		if (!(state->reading_from_stdin))
			ioctl(STDIN_FILENO, TIOCSPGRP, &(state->group_id));
		if (WIFSIGNALED(job->return_value))
			print_signal(WTERMSIG(job->return_value));
		if (job->state == JOB_STOPPED)
		{
			job->needs_status_print = true;
			state->stopped_jobs_warning_shown = false;
		}
	}
	else
	{
		job->state = JOB_CREATED;
		job_current_update(job, state);
	}
}

void	job_find_new_previous_job(t_state *state)
{
	int	i;

	i = MAX_JOBS - 1;
	while (i >= 0)
	{
		if (state->jobs[i].state != JOB_EMPTY
			&& state->current_job != &(state->jobs[i]))
		{
			state->previous_job = &(state->jobs[i]);
			return ;
		}
		i--;
	}
	state->previous_job = NULL;
}
