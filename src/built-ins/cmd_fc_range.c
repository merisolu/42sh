/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc_range.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:41:49 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/13 12:21:57 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

void	cmd_fc_parse_range(char *const *args, char *flags, t_fc_range *range,
t_state *state)
{
	int	length;
	int	offset;

	offset = ft_strchr(flags, 'e') != NULL;
	length = get_history_length(state);
	if (!args[0 + offset])
	{
		if (ft_strchr(flags, 'l'))
			range->start = ft_clamp(length - 15, 1, length);
		else
			range->start = length;
		range->end = length;
		return ;
	}
	range->start = ft_clamp(ft_atoi(args[0 + offset]), 1, length);
	if (args[1])
		range->end = ft_clamp(ft_atoi(args[1 + offset]), 1, length);
	else
		range->end = range->start + 1;
}

void	cmd_fc_reverse_range(t_fc_range *range)
{
	int	temp;

	temp = range->start;
	range->start = range->end;
	range->end = temp;
}
