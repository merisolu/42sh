/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_group.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:02:30 by jumanner          #+#    #+#             */
/*   Updated: 2023/10/19 15:31:05 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
 * Moves the pid to the first pid of the job, or if there's no valid first pid
 * creates a new process group. If 'foreground' is set to true, the process
 * group will be set as the foreground process group.
 */
pid_t	process_group_set(t_state *state, pid_t pid, pid_t first_pid, bool fg)
{
	pid_t	target;

	if (first_pid > 0)
		target = first_pid;
	else
		target = pid;
	if (setpgid(pid, target) == -1)
		return (-1);
	if (fg && !(state->reading_from_stdin))
	{
		if (ioctl(STDIN_FILENO, TIOCSPGRP, &target) == -1)
			return (-1);
	}
	return (target);
}
