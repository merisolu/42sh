/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_up.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:13:45 by amann             #+#    #+#             */
/*   Updated: 2023/03/27 16:39:37 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static void	free_and_reshuffle(t_auto *autocomp, int i)
{
	free((autocomp->search_result)[i]);
	while ((autocomp->search_result)[i])
	{
		(autocomp->search_result)[i] = (autocomp->search_result)[i + 1];
		i++;
	}
	return ;
}

/*
 *	Bubble sort to arrange the options into the correct order
 */
static void	sort_options(t_auto *ac)
{
	int		i;
	int		res;
	char	*temp;
	bool	swapped;

	swapped = false;
	i = 0;
	while ((ac->search_result)[i + 1])
	{
		res = ft_strcmp((ac->search_result)[i], (ac->search_result)[i + 1]);
		if (res == 0)
			free_and_reshuffle(ac, i);
		else if (res > 0)
		{
			temp = (ac->search_result)[i];
			(ac->search_result)[i] = (ac->search_result)[i + 1];
			(ac->search_result)[i + 1] = temp;
			swapped = true;
		}
		i++;
	}
	if (swapped)
		sort_options(autocomp);
	return ;
}

void	wrap_up(t_auto *autocomp)
{
	sort_options(autocomp);
	if (!(autocomp->auto_bools.second_tab)
		&& ft_null_array_len((void **)(autocomp->search_result)) > 1)
	{
		if (!filter_matching(autocomp))
			return ;
	}
	if (ft_null_array_len((void **)(autocomp->search_result)) == 1)
		truncate_result(autocomp);
	return ;
}
