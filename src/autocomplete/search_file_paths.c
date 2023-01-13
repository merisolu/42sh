/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_file_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:44:44 by amann             #+#    #+#             */
/*   Updated: 2023/01/13 16:39:09 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

size_t	last_slash(char *str)
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

static void	reset_query_and_path(char **query, char **path)
{
	char	*temp;

	*path = ft_strndup(*query, last_slash(*query));
	temp = ft_strdup(ft_strrchr(*query, '/') + 1);
	ft_strdel(query);
	*query = temp;
}

char	**search_file_paths(char **trimmed_input, bool second_tab)
{
	char	**search_result;
	char	*query;
	int		count;
	char	*path;
	t_auto	autocomp;

	search_result = (char **) ft_memalloc(sizeof(char *) * INPUT_MAX_SIZE); //check this is not exceeded while searching
	if (!search_result)
		return (print_error_ptr(NULL, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	count = 0;
	query = find_query(*trimmed_input, ' ');
	initialise_autocomp(&autocomp, &query, &search_result, &count);
	path = NULL;
	if (ft_strchr(query, '/'))
		reset_query_and_path(&query, &path);
	else
		path = ft_strdup("./");
	if (!path || !query)
		return (print_error_ptr(NULL, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	autocomp.query_len = ft_strlen(query);
	directory_search(path, &autocomp, false, false);
	free(path);
	free(query);
	return (wrap_up(autocomp, second_tab));
}
