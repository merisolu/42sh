/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:02:59 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/11 13:23:41 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	pids_add(pid_t pid, bool background, t_state *state)
{
	size_t	i;
	pid_t	*target;

	if (background)
		target = state->background_pids;
	else
		target = state->pids;
	i = 0;
	while (i < MAX_PIDS && target[i] != 0)
		i++;
	if (i == MAX_PIDS)
		return (false);
	target[i] = pid;
	if (background)
		ft_printf("[background process] %i\n", pid);
	return (true);
}

int	pids_wait(t_state *state)
{
	size_t	i;
	int		return_value;

	i = 0;
	return_value = state->last_return_value;
	while (state->pids[i] != 0)
	{
		if (state->pids[i] != -1)
		{
			waitpid(state->pids[i], &return_value, WUNTRACED);
			if (WIFSTOPPED(return_value))
				ft_printf("\n[stopped] %i", state->pids[i]);
			return_value = get_return_value_from_status(return_value);
		}
		i++;
	}
	ft_bzero(state->pids, sizeof(int) * MAX_PIDS);
	return (return_value);
}

void	pids_wait_background(t_state *state)
{
	size_t	i;

	i = 0;
	while (i < MAX_PIDS)
	{
		if (state->background_pids[i] > 0
			&& waitpid(state->background_pids[i], NULL, WNOHANG))
		{
			ft_printf("[done] %i\n", state->background_pids[i]);
			state->background_pids[i] = 0;
		}
		i++;
	}
}
