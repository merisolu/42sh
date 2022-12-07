/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:02:59 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/07 14:06:22 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	pids_add(pid_t pid, t_state *state)
{
	size_t	i;

	i = 0;
	while (i < MAX_PIDS && state->pids[i] != 0)
		i++;
	if (i == MAX_PIDS)
		return (false);
	state->pids[i] = pid;
	return (true);
}

int	pids_wait(t_state *state)
{
	size_t	i;
	int		return_value;

	i = 0;
	while (state->pids[i] != 0)
	{
		if (state->pids[i] != -1)
			waitpid(state->pids[i], &return_value, 0);
		i++;
	}
	ft_bzero(state->pids, sizeof(int) * MAX_PIDS);
	return (return_value);
}
