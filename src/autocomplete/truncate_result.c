/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truncate_result.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:41:37 by amann             #+#    #+#             */
/*   Updated: 2023/01/12 14:42:25 by amann            ###   ########.fr       */
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

//	ft_printf("%zu", autocomp.query_len);
	truncated = ft_strdup(((*(autocomp.search_results))[0]) + autocomp.query_len);
	ft_strdel(&((*(autocomp.search_results))[0]));
	if (!truncated)
	{
		print_error_ptr(NULL, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL);
		return ;
	}
	(*(autocomp.search_results))[0] = truncated;
	return ;
}
