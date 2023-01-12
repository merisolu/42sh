/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_up.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:13:45 by amann             #+#    #+#             */
/*   Updated: 2023/01/12 19:21:52 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

char	**wrap_up(t_auto autocomp, bool second_tab)
{
	if (*(autocomp.count) > 1 && !second_tab && !filter_matching(autocomp))
	{
		ft_free_null_array((void **)*(autocomp.search_results));
		return (NULL);
	}
	if (ft_null_array_len((void **) *(autocomp.search_results)) == 1)
		truncate_result(autocomp);
	return (*(autocomp.search_results));
}
