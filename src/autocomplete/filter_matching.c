/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_matching.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:38:58 by amann             #+#    #+#             */
/*   Updated: 2023/01/18 17:13:27 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static char	*create_new_string(t_auto autocomp, size_t max_len)
{
	char	*new_string;

	new_string = ft_strnew(max_len);
	if (!new_string)
		return ((char *)print_error_ptr(NULL, ERRTEMPLATE_SIMPLE,
				ERR_MALLOC_FAIL));
	ft_strcpy(new_string, *(autocomp.query));
	return (new_string);
}

static void	filter_loop(t_auto autocomp, size_t *i, bool *flag, char c)
{
	size_t	idx;

	idx = 0;
	while ((*(autocomp.search_results))[idx])
	{
		if ((*(autocomp.search_results))[idx][*i] != c)
		{
			*flag = true;
			break ;
		}
		else
			idx++;
	}
	return ;
}

static bool	update_results(t_auto autocomp, char *new_string)
{
	ft_free_null_array((void **)*(autocomp.search_results));
	*(autocomp.search_results) = (char **) ft_memalloc(sizeof(char *) * 2);
	if (!(*(autocomp.search_results)))
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	(*(autocomp.search_results))[0] = new_string;
	return (true);
}

static bool	free_return_false(char *str)
{
	free(str);
	return (false);
}

bool	filter_matching(t_auto autocomp, bool *filtered)
{
	size_t	max_len;
	size_t	i;
	char	*new_string;
	bool	flag;

	max_len = find_longest(*(autocomp.search_results));
	new_string = create_new_string(autocomp, max_len);
	if (!new_string)
		return (false);
	flag = false;
	i = autocomp.query_len;
	while (i < max_len)
	{
		filter_loop(autocomp, &i, &flag, (*(autocomp.search_results))[0][i]);
		if (flag && i == autocomp.query_len)
			return (free_return_false(new_string));
		else if (flag)
			break ;
		new_string[i] = (*(autocomp.search_results))[0][i];
		i++;
	}
	*filtered = true;
	return (update_results(autocomp, new_string));
}
