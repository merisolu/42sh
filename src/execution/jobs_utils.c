/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:39:28 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/24 10:58:01 by jumanner         ###   ########.fr       */
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
	state->previous_job = state->current_job;
	state->current_job = new_current;
}
