/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_jobs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:11:48 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/13 14:01:50 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	cmd_jobs(char *const *args, t_state *state)
{
	size_t	i;
	t_job	*job;

	(void)args;
	i = 0;
	while (i < MAX_JOBS)
	{
		job = &(state->jobs[i]);
		if (job->state == JOB_EMPTY || job->state == JOB_CREATED
			|| job->state == JOB_DONE)
		{
			i++;
			continue ;
		}
		job_print(job, state);
		i++;
	}
	return (0);
}
