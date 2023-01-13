/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:16:26 by amann             #+#    #+#             */
/*   Updated: 2023/01/13 16:40:43 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static bool	search_builtins(char *query, char ***sr, int *count, size_t len)
{
	const t_cmd_dispatch	*builtins;
	size_t					i;

	builtins = get_built_in_dispatch();
	i = 0;
	while (builtins[i].run != NULL)
	{
		if (ft_strnequ(
				query, builtins[i].name, len))
		{
			(*sr)[*count] = ft_strdup((char *)builtins[i].name);
			if (!(*sr)[*count])
			{
				return (print_error_bool(false, ERRTEMPLATE_SIMPLE,
						ERR_MALLOC_FAIL));
			}
			(*count)++;
		}
		i++;
	}
	return (true);
}

static char	**get_paths(t_state *state)
{
	char	*path_var;

	path_var = env_get("PATH", state->env);
	if (!path_var)
		path_var = env_get("PATH", state->intern);
	if (!path_var)
		return (NULL);
	return (ft_strsplit(path_var, ':'));
}

static char	**free_all_return(char ***search_result, char ***paths)
{
	ft_free_null_array((void **)*search_result);
	ft_free_null_array((void **)*paths);
	*search_result = NULL;
	*paths = NULL;
	return (NULL);
}

/*
 * In the event that we are looking for a command, we much search from our list
 * of builtins, and then the path, to compile a list of potential commands.
 *
 * If the PATH cannot be found in the environment, we must also look for it in
 * the internal variables, as this is what bash seems to do.
 *
 * If there is more than 1 possible solution, we check if there matching chars
 * beyond the end of the query string in all possible results. Otherwise, we
 * stop unless there is a second tab press.
 */

char	**search_commands(t_state *state, char **ti, bool second_tab)
{
	char	**search_result;
	char	**paths;
	int		count;
	int		i;
	t_auto	autocomp;

	paths = get_paths(state);
	search_result = (char **) ft_memalloc(sizeof(char *) * INPUT_MAX_SIZE);
	if (!paths || !search_result)
		print_error_ptr(NULL, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL);
	count = 0;
	initialise_autocomp(&autocomp, ti, &search_result, &count);
	autocomp.query_len = ft_strlen(*ti);
	if (!search_builtins(*ti, &search_result, &count, autocomp.query_len))
		return (NULL);
	i = 0;
	while (paths[i])
	{
		if (directory_search(paths[i], &autocomp, true, false) == -1)
			return (free_all_return(&search_result, &paths));
		i++;
	}
	ft_free_null_array((void **)paths);
	if (ft_null_array_len((void **)search_result) == 0)
	{
		char *query;
		char *path;
		t_auto autocomp2;
		//search dirs for executables
		if (ft_strequ(*ti, "."))
		{
			search_result[0] = ft_strdup("./");
			return (wrap_up(autocomp, second_tab));
		}
		else if (ft_strequ(*ti, "/"))
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
			ft_putendl("KO");
			query = ft_strdup(*ti);
			path = ft_strdup("./");
		}
		initialise_autocomp(&autocomp2, &query, &search_result, &count);
		autocomp2.query_len = ft_strlen(query);
		ft_printf("\n%s %s\n", path, query);
		directory_search(path, &autocomp2, false, true);
		free(path);
		free(query);
		return (wrap_up(autocomp2, second_tab));
	}
	return (wrap_up(autocomp, second_tab));
}
