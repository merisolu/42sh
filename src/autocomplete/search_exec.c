/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:03:36 by amann             #+#    #+#             */
/*   Updated: 2023/02/06 14:59:55 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

char	**check_exec(t_auto autocomp, char **query, bool second_tab, \
		bool *filtered, t_state *state)
{
	if (ft_strequ(*query, "."))
	{
		(*(autocomp.search_results))[0] = ft_strdup("./");
		free(*query);
		return (wrap_up(&autocomp, second_tab, filtered));
	}
	return (search_exec(autocomp.search_results, query, second_tab, filtered, state));
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

static void	set_path_query(char **path, char **query, char **orig, t_state *state)
{
	if (ft_strequ(*orig, "/"))
	{
		*query = ft_strdup("");
		*path = ft_strdup("/");
	}
	else if (ft_strchr(*orig, '/'))
	{
		*query = find_query(*orig, '/', state, true);
		*path = ft_strndup(*orig, last_slash(*orig));
	}
	else
	{
		*query = ft_strdup(*orig);
		*path = ft_strdup("./");
	}
}

char	**search_exec(char ***sr, char **orig, bool second_tab, bool *filtered, t_state *state)
{
	char	*query;
	char	*path;
	int		count;
	t_auto	autocomp;

	query = NULL;
	path = NULL;
	set_path_query(&path, &query, orig, state);
	if (!check_allocations(path, query))
		return (NULL);
	count = 0;
	initialise_autocomp(&autocomp, &query, sr, &count);
	autocomp.query_len = ft_strlen(query);
	directory_search(path, &autocomp, false, true);
	free(path);
	free(query);
	free(*orig);
	return (wrap_up(&autocomp, second_tab, filtered));
}
