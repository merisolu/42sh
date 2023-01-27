/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc_range.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:41:49 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/27 11:21:40 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static int	get_history_length(t_state *state)
{
	int	i;

	i = HISTORY_SIZE - 2;
	while (i >= 0 && state->history[i] != '\0')
		i--;
	return (HISTORY_SIZE - i - 2);
}

void	cmd_fc_parse_range(char *const *args, t_fc_range *range, t_state *state)
{
	int	length;

	length = get_history_length(state);
	if (!args[0])
	{
		range->start = length - 15;
		range->end = length;
		return ;
	}
	range->start = ft_clamp(atoi(args[0]), 1, length);
	if (args[1])
		range->end = ft_clamp(atoi(args[1]), 1, length);
	else
		range->end = range->start + 1;
}

int	cmd_fc_range_number_to_index(int num, t_state *state)
{
	return (get_history_length(state) - num + 1);
}

void	cmd_fc_reverse_range(t_fc_range *range)
{
	int	temp;

	temp = range->start;
	range->start = range->end;
	range->end = temp;
}
