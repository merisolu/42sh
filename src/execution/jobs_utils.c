/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:39:28 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/19 14:47:28 by jumanner         ###   ########.fr       */
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

/*
 * Finds a job in the jobs array of state with the matching id. Returns NULL if
 * nothing was found.
 */
static t_job	*find_job_with_id(int id, t_state *state)
{
	size_t	i;

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
 */
t_job	*job_id_to_job(char *id, t_state *state)
{
	size_t	length;
	int		numerical_id;

	if (!id || id[0] != '%')
		return (NULL);
	length = ft_strlen(id);
	if (length == 1 || (length == 2 && (id[1] == '%' || id[1] == '+')))
		return (state->current_job);
	if (length == 2 && id[1] == '-')
		return (state->previous_job);
	if (ft_isdigit_str(id + 1))
	{
		numerical_id = ft_atoi(id + 1);
		return (find_job_with_id(numerical_id, state));
	}
	if (id[1] == '?')
		return (find_job_with_command(id + 2, true, state));
	return (find_job_with_command(id + 1, false, state));
}
