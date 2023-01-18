/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:03:36 by amann             #+#    #+#             */
/*   Updated: 2023/01/18 17:13:04 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

char	**check_exec(t_auto autocomp, char **ti, bool second_tab, \
		bool *filtered)
{
	if (ft_strequ(*ti, "."))
	{
		(*(autocomp.search_results))[0] = ft_strdup("./");
		return (wrap_up(&autocomp, second_tab, filtered));
	}
	return (search_exec(autocomp.search_results, ti, second_tab, filtered));
}

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

static void	set_path_query(char **path, char **query, char **ti)
{
	if (ft_strequ(*ti, "/"))
	{
		*query = ft_strdup("");
		*path = ft_strdup("/");
	}
	else if (ft_strchr(*ti, '/'))
	{
		*query = find_query(*ti, '/');
		*path = ft_strndup(*ti, last_slash(*ti));
	}
	else
	{
		*query = ft_strdup(*ti);
		*path = ft_strdup("./");
	}
}

char	**search_exec(char ***sr, char **ti, bool second_tab, bool *filtered)
{
	char	*query;
	char	*path;
	int		count;
	t_auto	autocomp;

	query = NULL;
	path = NULL;
	set_path_query(&path, &query, ti);
	if (!check_allocations(path, query))
		return (NULL);
	count = 0;
	initialise_autocomp(&autocomp, &query, sr, &count);
	autocomp.query_len = ft_strlen(query);
	directory_search(path, &autocomp, false, true);
	free(path);
	free(query);
	return (wrap_up(&autocomp, second_tab, filtered));
}
