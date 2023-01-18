/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:00:53 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/18 11:01:38 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	*get_state_string(t_job_state state)
{
	if (state == JOB_RUNNING)
		return ("Running");
	if (state == JOB_STOPPED)
		return ("Stopped");
	return ("Done");
}

/*
 * Prints the given job.
 */
void	job_print(t_job *job, char format, t_state *state)
{
	char	current;

	if (job->state == JOB_CREATED)
	{
		ft_printf(JOB_BACKGROUND_CREATED_PRINT, job->id, job_get_last_pid(job));
		return ;
	}
	current = ' ';
	if (job == state->current_job)
		current = '+';
	if (format == 'p')
		ft_printf(JOB_PID_STATUS_PRINT, job->pids[0]);
	else if (format == 'l')
		ft_printf(JOB_LONG_STATUS_PRINT, job->id, current, job->pids[0],
			get_state_string(job->state), job->command);
	else
		ft_printf(JOB_STATUS_PRINT, job->id, current,
			get_state_string(job->state), job->command);
}