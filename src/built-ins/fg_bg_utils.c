/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_bg_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:21:51 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/24 14:34:09 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

t_job	*get_job(char *const *args, t_state *state)
{
	t_job	*job;

	if (args[1] != NULL)
	{
		job = job_id_to_job(args[1], state);
		if (job && job->state == JOB_CREATED)
			job = NULL;
		if (!job)
			print_error(1, ERRTEMPLATE_DOUBLE_NAMED,
				args[0], args[1], ERR_NO_SUCH_JOB);
		return (job);
	}
	if (!state->current_job)
		print_error(1, ERRTEMPLATE_DOUBLE_NAMED,
			args[0], "current", ERR_NO_SUCH_JOB);
	job = state->current_job;
	return (job);
}
