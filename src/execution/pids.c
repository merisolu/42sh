/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:02:59 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/26 13:02:46 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
 * Adds the given pid to the pids array of the given job. If pid == 0, it will
 * be ignored. Returns true on success, false if the pid array is full.
 */
bool	pids_add(pid_t pid, t_job *job)
{
	size_t	i;

	if (pid == 0)
		return (true);
	i = 0;
	while (i < MAX_PIDS && job->pids[i] != 0)
		i++;
	if (i == MAX_PIDS)
		return (false);
	job->pids[i] = pid;
	return (true);
}

/*
 * Waits for the given pid and update's the state of the job accordingly. If
 * no_hang is set to true, the call to waitpid() won't block.
 */
void	pid_wait(t_job *job, pid_t pid, bool no_hang)
{
	int			status;
	int			wait_flags;
	t_job_state	old_state;

	if (pid <= 0)
		return ;
	wait_flags = WUNTRACED;
	if (no_hang)
		wait_flags |= WNOHANG;
	if (waitpid(pid, &status, wait_flags) <= 0)
		return ;
	old_state = job->state;
	if (WIFSTOPPED(status))
		job->state = JOB_STOPPED;
	else if (WIFEXITED(status) || WIFSIGNALED(status))
		job->state = JOB_DONE;
	else
		job->state = JOB_RUNNING;
	if (old_state != JOB_CREATED)
		job->needs_status_print = old_state != job->state;
	job->return_value = status;
}

/*
 * Waits all pids in a given job to remove zombie processes. Empties the pids
 * array after that.
*/
void	pids_clean_up(t_job *job)
{
	size_t	i;

	i = 0;
	while (job->pids[i] > 0)
	{
		if (job->pids[i] > 0)
			waitpid(job->pids[i], NULL, WNOHANG);
		i++;
	}
	ft_bzero(job->pids, sizeof(pid_t) * MAX_PIDS);
}
