/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:03:36 by amann             #+#    #+#             */
/*   Updated: 2023/01/16 13:23:04 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

/*
 *	If we cannot find a matching executable on the path, or a builtin, we then
 *	need to treat the query as a path to an executable elsewhere in the
 *	filesystem.
 *
 */

static bool	check_allocations(char *path, char *query)
{
	if (!path)
	{
		if (query)
			free(query);
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE,
				ERR_MALLOC_FAIL));
	}
	if (!query)
	{
		if (path)
			free(path);
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE,
				ERR_MALLOC_FAIL));
	}
	return (true);
}

char	**search_exec(char ***sr, char **ti, bool second_tab)
{
	char	*query;
	char	*path;
	int		count;
	t_auto	autocomp;

	if (ft_strequ(*ti, "/"))
	{
		query = ft_strdup("");
		path = ft_strdup("/");
	}
	else if (ft_strchr(*ti, '/'))
	{
		query = find_query(*ti, '/');
		path = ft_strndup(*ti, last_slash(*ti));
	}
	else
	{
		query = ft_strdup(*ti);
		path = ft_strdup("./");
	}
	if (!check_allocations(path, query))
		return (NULL);
	count = 0;
	initialise_autocomp(&autocomp, &query, sr, &count);
	autocomp.query_len = ft_strlen(query);
//	ft_printf("\n%s %s %d\n", path, query, (int)autocomp.query_len);
	directory_search(path, &autocomp, false, true);
	free(path);
	free(query);
	return (wrap_up(autocomp, second_tab));
}
