/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:51:58 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/13 08:53:20 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
 * Finds a job in the jobs array of state with the matching id. Returns NULL if
 * nothing was found.
 */
static t_job	*find_job_with_id(int id, t_state *state)
{
	size_t	i;

	if (id <= 0)
		return (NULL);
	i = 0;
	while (i < MAX_JOBS)
	{
		if (state->jobs[i].id == id)
			return (&(state->jobs[i]));
		i++;
	}
	return (NULL);
}

/*
 * Finds a job in the jobs array of the state with the matching command name. If
 * 'contains' is set to true, the whole command string  is searched for
 * a possible match. If false, only the start of the command is checked.
 * Returns NULL if nothing was found. If there are multiple matching jobs,
 * an ambiguous job spec error is printed, and NULL is returned.
 */
static t_job	*find_job_with_command(char *cmd, bool contains, t_state *state)
{
	size_t	i;
	t_job	*job;
	t_job	*result;

	result = NULL;
	i = 0;
	while (i < MAX_JOBS)
	{
		job = &(state->jobs[i]);
		if (job->state != JOB_CREATED && job->state != JOB_EMPTY \
			&& ((contains && ft_strstr(job->command, cmd)) \
			|| (!contains && ft_strnequ(job->command, cmd, ft_strlen(cmd)))))
		{
			if (result)
			{
				print_error(0, ERRTEMPLATE_DOUBLE_NAMED, "jobs",
					cmd, ERR_AMBIGUOUS_JOB_SPEC);
				return (NULL);
			}
			else
				result = job;
		}
		i++;
	}
	return (result);
}

/*
 * Attempts to find a job matching the given job control job id. Possible
 * valid ids are:
 *
 * %, %%, %-, %-, %n, %string, %?string
 *
 * Variants of the above without the % at the beginning are also accepted.
 */
t_job	*job_id_to_job(char *id, t_state *state)
{
	size_t	length;
	int		numerical_id;

	if (!id)
		return (NULL);
	if (id[0] == '%')
		id++;
	length = ft_strlen(id);
	if (length == 0 || (length == 1 && (id[0] == '%' || id[0] == '+')))
		return (state->current_job);
	if (length == 1 && id[0] == '-')
		return (state->previous_job);
	if (ft_isdigit_str(id))
	{
		numerical_id = ft_atoi(id);
		return (find_job_with_id(numerical_id, state));
	}
	if (id[0] == '?')
		return (find_job_with_command(id + 1, true, state));
	return (find_job_with_command(id, false, state));
}
