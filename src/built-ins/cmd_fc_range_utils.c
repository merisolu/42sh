/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc_range_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:35:10 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/21 14:35:26 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

void	cmd_fc_reverse_range(t_fc_range *range)
{
	int	temp;

	temp = range->start;
	range->start = range->end;
	range->end = temp;
}
