/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:51:58 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/13 11:01:14 by jumanner         ###   ########.fr       */
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
		if (state->jobs[i].id == id && state->jobs[i].state != JOB_EMPTY)
			return (&(state->jobs[i]));
		i++;
	}
	return (NULL);
}

/*
 * Finds a job in the jobs array of the state with the matching command name. If
 * 'contains' is set to true, the whole command string  is searched for
 * a possible match. If false, only the start of the command is checked.
 *
 * The found job will be placed into *result. Possible return values are
 * either JOB_FIND_FOUND, JOB_FIND_NOT_FOUND, or JOB_FIND_AMBIGUOUS.
 */
static int	find_job_with_command(char *cmd, bool contains,
										t_state *state, t_job **result)
{
	size_t	i;
	t_job	*job;

	*result = NULL;
	i = 0;
	while (i < MAX_JOBS)
	{
		job = &(state->jobs[i]);
		if (job->state != JOB_CREATED && job->state != JOB_EMPTY \
			&& ((contains && ft_strstr(job->command, cmd)) \
			|| (!contains && ft_strnequ(job->command, cmd, ft_strlen(cmd)))))
		{
			if (*result)
			{
				*result = NULL;
				return (JOB_FIND_AMBIGUOUS);
			}
			else
				*result = job;
		}
		i++;
	}
	if (*result)
		return (JOB_FIND_FOUND);
	return (JOB_FIND_NOT_FOUND);
}

/*
 * Attempts to find a job matching the given job control job id. Possible
 * valid ids are:
 *
 * %, %%, %-, %-, %n, %string, %?string
 *
 * Variants of the above without the % at the beginning are also accepted.
 *
 * The found job will be placed into *result. Possible return values are
 * either JOB_FIND_FOUND, JOB_FIND_NOT_FOUND, or JOB_FIND_AMBIGUOUS.
 */
int	job_id_to_job(char *id, t_state *state, t_job **result)
{
	size_t	length;

	*result = NULL;
	if (!id)
		return (JOB_FIND_NOT_FOUND);
	if (id[0] == '%')
		id++;
	length = ft_strlen(id);
	if (length == 0 || (length == 1 && (id[0] == '%' || id[0] == '+')))
		*result = state->current_job;
	else if (length == 1 && id[0] == '-')
		*result = state->previous_job;
	else if (ft_isdigit_str(id))
		*result = find_job_with_id(ft_atoi(id), state);
	else if (id[0] == '?')
		return (find_job_with_command(id + 1, true, state, result));
	else
		return (find_job_with_command(id, false, state, result));
	if (*result)
		return (JOB_FIND_FOUND);
	return (JOB_FIND_NOT_FOUND);
}

/*
 * Prints an error message if the value provided matches either
 * JOB_FIND_NOT_FOUND or JOB_FIND_AMBIGUOUS.
 *
 * Returns 1 if an error was printed, 0 otherwise.
 */
int	job_id_to_job_error_print(int value, char *caller, char *id)
{
	if (value == JOB_FIND_NOT_FOUND)
		return (print_error(1, ERRTEMPLATE_DOUBLE_NAMED, caller,
				id, ERR_NO_SUCH_JOB));
	else if (value == JOB_FIND_AMBIGUOUS)
		return (print_error(1, ERRTEMPLATE_DOUBLE_NAMED, caller,
				id, ERR_AMBIGUOUS_JOB_SPEC));
	return (0);
}
