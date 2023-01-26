/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:34:04 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/26 13:03:00 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
 * Sets up a new job in the state->jobs array and returns it. Returns NULL on
 * error.
 * 
 * The command text needs to be updated to only take the specific section
 * of input that created this job!
 */
t_job	*jobs_create(t_ast *ast, t_state *state)
{
	int	i;

	i = 0;
	while (i < MAX_JOBS)
	{
		if (state->jobs[i].state != JOB_EMPTY)
		{
			i++;
			continue ;
		}
		ft_bzero(&(state->jobs[i]), sizeof(t_job));
		state->jobs[i].command = ast_to_string(ast);
		if (!state->jobs[i].command)
		{
			print_error(0, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL);
			return (NULL);
		}
		state->jobs[i].id = i + 1;
		ft_bzero(&(state->jobs[i].pids), sizeof(pid_t) * MAX_PIDS);
		state->jobs[i].state = JOB_CREATED;
		return (&(state->jobs[i]));
	}
	print_error(0, ERRTEMPLATE_SIMPLE, "max job count reached");
	return (NULL);
}

/*
 * Waits for a job to finish, or if no_hang is set to true, check's job's
 * progress. Update's state->current_job when necessary. Sets the state's
 * return value if blocking.
 */
void	job_wait(t_job *job, bool no_hang, t_state *state)
{
	pid_wait(job, job_get_last_pid(job), no_hang);
	if (job->state == JOB_STOPPED)
		job_current_update(job, state);
	if (job->state == JOB_DONE)
		pids_clean_up(job);
	else
		return ;
	if (!no_hang)
		set_return_value(
			get_return_value_from_status(job->return_value), state);
}

/*
 * Update status of all jobs in the state->jobs array. 
 */
void	jobs_check_status(t_state *state)
{
	size_t	i;

	i = 0;
	while (i < MAX_JOBS)
	{
		if (state->jobs[i].state == JOB_RUNNING
			|| state->jobs[i].state == JOB_STOPPED)
			job_wait(&(state->jobs[i]), true, state);
		else if (state->jobs[i].state == JOB_CREATED)
			state->jobs[i].state = JOB_RUNNING;
		i++;
	}
}

/*
 * Prints the status of any job which needs to have it's status printed.
 */
void	jobs_print_changed(t_state *state)
{
	size_t	i;

	i = 0;
	while (i < MAX_JOBS)
	{
		if (state->jobs[i].needs_status_print)
		{
			job_print(&(state->jobs[i]), '\0', state);
			state->jobs[i].needs_status_print = false;
		}
		i++;
	}	
}

/*
 * Cleans up finished jobs from the jobs list.
 */
void	jobs_cleanup_finished(t_state *state)
{
	size_t	i;

	i = 0;
	while (i < MAX_JOBS)
	{
		if (state->jobs[i].pids[0] == 0 || state->jobs[i].state == JOB_DONE)
		{
			state->jobs[i].state = JOB_EMPTY;
			if (&(state->jobs[i]) == state->current_job)
				job_current_update(state->previous_job, state);
			else if (&(state->jobs[i]) == state->previous_job)
				job_find_new_previous_job(state);
			ft_memdel((void **)&(state->jobs[i].command));
		}
		i++;
	}
}
