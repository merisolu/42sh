/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:03:36 by amann             #+#    #+#             */
/*   Updated: 2023/03/23 17:59:55 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

void	check_exec(t_auto *autocomp, t_state *state)
{
	if (ft_strequ(*(autocomp->query), "."))
	{
		(autocomp->search_result_final)[0] = ft_strdup("./");
		free(*(autocomp->query));
		wrap_up(autocomp);
		return ;
	}
	
	(void) state;
	return ;
	//return (search_exec(autocomp, state));
}

/*
 *	If we cannot find a matching executable on the path, or a builtin, we then
 *	need to treat the query as a path to an executable elsewhere in the
 *	filesystem.
 *
 */
/*
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
		free(path);
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE,
				ERR_MALLOC_FAIL));
	}
	return (true);
}

static void	set_path_query(char **path, char **query, char **orig, \
		t_state *state)
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
*/

// this is called from check exec via search commands, needs some work...
// maybe scrap and start again once the program will compile and run again.

void search_exec(t_auto *autocomp, t_state *state)
{
	(void) autocomp;
	(void) state;
	return ;
/*	char	*query;
	char	*path;
	int		count;
	t_auto	autocomp;

	query = NULL;
	path = NULL;
	set_path_query(&path, &query, orig, state);
	if (!check_allocations(path, query))
		return (NULL);
	count = 0;
	//initialise_autocomp(&autocomp, &query, sr, &count);
	autocomp.query_len = ft_strlen(query);
	directory_search(path, &autocomp, false, true);
	free(path);
	free(*orig);
	return (wrap_up(&autocomp, a_bools));*/
}
