/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:00:53 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/25 15:50:42 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	print_state(t_job_state state, int value)
{
	if (state == JOB_RUNNING)
		ft_putstr("Running");
	else if (state == JOB_STOPPED)
	{
		if (WSTOPSIG(value) == SIGSTOP)
			ft_putstr("Stopped (SIGSTOP)");
		else if (WSTOPSIG(value) == SIGTTIN)
			ft_putstr("Stopped (SIGTTIN)");
		else if (WSTOPSIG(value) == SIGTTOU)
			ft_putstr("Stopped (SIGTTOU)");
		else
			ft_putstr("Stopped");
	}
	else if (WIFSIGNALED(value) != 0)
		ft_printf("Terminated (%i)", WTERMSIG(value));
	else if (WEXITSTATUS(value) != 0)
		ft_printf("Done (%i)", WEXITSTATUS(value));
	else
		ft_putstr("Done");
}

static bool	job_create_print(t_job *job)
{
	if (job->state == JOB_CREATED)
		ft_printf(JOB_BACKGROUND_CREATED_PRINT, job->id, job_get_last_pid(job));
	return (job->state == JOB_CREATED);
}

/*
 * Prints the given job.
 */
void	job_print(t_job *job, char format, t_state *state)
{
	char	current;

	if (job_create_print(job))
		return ;
	if (format == 'p')
	{
		ft_printf(JOB_PID_PRINT, job->pids[0]);
		return ;
	}
	current = ' ';
	if (job == state->current_job)
		current = '+';
	else if (job == state->previous_job)
		current = '-';
	if (format == 'l')
		ft_printf(JOB_PRINT_START_LONG, job->id, current, job->pids[0]);
	else
		ft_printf(JOB_PRINT_START, job->id, current);
	print_state(job->state, job->return_value);
	if (job->state == JOB_RUNNING)
		ft_printf(JOB_PRINT_END_RUNNING, job->command);
	else
		ft_printf(JOB_PRINT_END, job->command);
}
