/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_up.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:13:45 by amann             #+#    #+#             */
/*   Updated: 2023/02/22 13:15:31 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static void	free_and_reshuffle(char ***sr, int i)
{
	free((*sr)[i]);
	while ((*sr)[i])
	{
		(*sr)[i] = (*sr)[i + 1];
		i++;
	}
}

static void	sort_options(char ***sr)
{
	int		i;
	int		res;
	char	*temp;
	bool	swapped;

	swapped = false;
	i = 0;
	while ((*sr)[i + 1])
	{
		res = ft_strcmp((*sr)[i], (*sr)[i + 1]);
		if (res == 0)
			free_and_reshuffle(sr, i);
		else if (res > 0)
		{
			temp = (*sr)[i];
			(*sr)[i] = (*sr)[i + 1];
			(*sr)[i + 1] = temp;
			swapped = true;
		}
		i++;
	}
	if (swapped)
		sort_options(sr);
}

char	**wrap_up(t_auto *autocomp, t_auto_bools *a_bool)
{
	sort_options(autocomp->search_results);
	if (!(a_bool->second_tab)
		&& ft_null_array_len((void **)(*(autocomp->search_results))) > 1)
	{
		if (!filter_matching(*autocomp, a_bool))
		{
			ft_free_null_array((void **)*(autocomp->search_results));
			free(*(autocomp->query));
			return (NULL);
		}
	}
	if (ft_null_array_len((void **)*(autocomp->search_results)) == 1)
		truncate_result(*autocomp);
	free(*(autocomp->query));
	return (*(autocomp->search_results));
}
