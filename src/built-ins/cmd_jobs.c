/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_jobs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:11:48 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/18 11:08:42 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static void	on_error(char c)
{
	ft_dprintf(STDERR_FILENO, "42sh: jobs: -%c: invalid option\n", c);
	ft_putstr_fd("jobs: usage: jobs [-l|-p] [job_id...]\n", STDERR_FILENO);
}

int	cmd_jobs(char *const *args, t_state *state)
{
	char	flags[3];
	size_t	i;
	t_job	*job;

	if (parse_flags(args + 1, "lp", flags, &on_error) == -1)
		return (2);
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
		if (ft_strchr(flags, 'p'))
			job_print(job, 'p', state);
		else if (ft_strchr(flags, 'l'))
			job_print(job, 'l', state);
		else
			job_print(job, '\0', state);
		i++;
	}
	return (0);
}
