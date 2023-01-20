/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_longest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:15:57 by amann             #+#    #+#             */
/*   Updated: 2023/01/17 15:16:22 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

size_t	find_longest(char **search_results)
{
	size_t	max;
	size_t	current_len;
	size_t	i;

	max = 0;
	i = 0;
	while (search_results[i])
	{
		current_len = ft_strlen(search_results[i]);
		if (current_len > max)
			max = current_len;
		i++;
	}
	return (max);
}
