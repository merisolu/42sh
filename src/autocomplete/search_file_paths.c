/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_file_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:44:44 by amann             #+#    #+#             */
/*   Updated: 2023/01/12 17:49:41 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static char	*find_query(char *str)
{
	size_t	len;
	size_t	start;

	len = ft_strlen(str);
	start = 0;
	while (len)
	{
		if (str[len] == ' ')
			start = len + 1;
		len--;
	}
	return (ft_strdup(str + start));
}

static size_t	last_slash(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	while (len)
	{
		if (str[len] == '/')
			break ;
		len--;
	}
	return (len + 1);
}

char	**search_file_paths(char **trimmed_input, bool second_tab)
{
	char	**search_result;
	char	*query;
	int		count;
	char	*path;
	char	*temp;
	t_auto	autocomp;

	search_result = (char **) ft_memalloc(sizeof(char *) * 200);
	if (!search_result)
		print_error_ptr(NULL, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL);
	count = 0;
	query = find_query(*trimmed_input);
	initialise_autocomp(&autocomp, &query, &search_result, &count);
	if (ft_strchr(query, '/'))
	{
		path = ft_strndup(query, last_slash(query));
		temp = ft_strdup(ft_strrchr(query, '/') + 1);
		ft_strdel(&query);
		query = temp;
	}
	else
		path = ft_strdup("./");
//	ft_printf("\npath = %s | query = %s\n", path, query);
	autocomp.query_len = ft_strlen(query);
	directory_search(path, &autocomp, false);
	free(path);
	free(query);
	if (count > 1 && !second_tab && !filter_matching(autocomp))
	{
		ft_free_null_array((void **)search_result);
		return (NULL);
	}
	if (ft_null_array_len((void **) *(autocomp.search_results)) == 1)
		truncate_result(autocomp);
	return (search_result);
}
