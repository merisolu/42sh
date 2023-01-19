/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_jobs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:11:48 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/19 14:43:53 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static void	on_error(char c)
{
	ft_dprintf(STDERR_FILENO, "42sh: jobs: -%c: invalid option\n", c);
	ft_putstr_fd("jobs: usage: jobs [-l|-p] [job_id...]\n", STDERR_FILENO);
}

static void	print_job(t_job *job, char *flags, t_state *state)
{
	if (job->state == JOB_EMPTY || job->state == JOB_CREATED
		|| job->state == JOB_DONE)
		return ;
	if (ft_strchr(flags, 'p'))
		job_print(job, 'p', state);
	else if (ft_strchr(flags, 'l'))
		job_print(job, 'l', state);
	else
		job_print(job, '\0', state);
}

static void	print_all_jobs(char *flags, t_state *state)
{
	size_t	i;
	t_job	*job;

	i = 0;
	while (i < MAX_JOBS)
	{
		job = &(state->jobs[i]);
		print_job(job, flags, state);
		i++;
	}
}

int	cmd_jobs(char *const *args, t_state *state)
{
	char	flags[3];
	t_job	*job;
	int		i;
	int		return_value;

	i = parse_flags(args + 1, "lp", flags, &on_error);
	if (i == -1)
		return (2);
	if (i == 0)
		i++;
	return_value = 0;
	if (!args[i])
		print_all_jobs(flags, state);
	while (args[i])
	{
		job = job_id_to_job(args[i], state);
		if (job)
			print_job(job, flags, state);
		else
			return_value = print_error(1, ERRTEMPLATE_DOUBLE_NAMED, "jobs",
					args[i], ERR_NO_SUCH_JOB);
		i++;
	}
	return (return_value);
}
