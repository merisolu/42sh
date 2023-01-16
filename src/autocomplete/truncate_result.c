/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truncate_result.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:41:37 by amann             #+#    #+#             */
/*   Updated: 2023/01/16 20:13:47 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

/*
 * If there is only one search result, we need to chop it down so that the
 * part needed to complete the string can be appeneded onto the input.
 *
 * We create a new string which is the length of the result - the length
 * of the search query.
 */

void	truncate_result(t_auto autocomp)
{
	char	*truncated;
	char	*temp;

	truncated = ft_strdup(
			((*(autocomp.search_results))[0]) + autocomp.query_len
			);
	ft_strdel(&((*(autocomp.search_results))[0]));
	if (!truncated)
	{
		print_error_ptr(NULL, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL);
		return ;
	}
	if (*(autocomp.count) == 1)
	{
		if (truncated[ft_strlen(truncated) - 1] != '/')
		{
			temp = ft_strnew(sizeof(char) * (ft_strlen(truncated) + 1));
			ft_strcpy(temp, truncated);
			temp[ft_strlen(truncated)] = ' ';
			free(truncated);
			truncated = temp;
		}
	}
	(*(autocomp.search_results))[0] = truncated;
	return ;
}
