/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:16:26 by amann             #+#    #+#             */
/*   Updated: 2023/01/12 14:43:48 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static bool	search_builtins(char *query, char ***search_result, int *count)
{
	const t_cmd_dispatch	*builtins;
	size_t					i;
	size_t					len;

	builtins = get_built_in_dispatch();
	len = ft_strlen(query);
	i = 0;
	while (builtins[i].run != NULL)
	{
		if (ft_strnequ(
				query, builtins[i].name, len))
		{
			(*search_result)[*count] = ft_strdup((char *)builtins[i].name);
			if (!(*search_result)[*count])
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

char	**search_commands(t_state *state, char *trimmed_input, bool second_tab)
{
	char	**search_result;
	char	**paths;
	int		count;
	int		i;
	t_auto	autocomp;

	paths = get_paths(state);
	search_result = (char **) ft_memalloc(sizeof(char *) * 200);
	if (!paths || !search_result)
		print_error_ptr(NULL, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL);
	count = 0;
	if (!search_builtins(trimmed_input, &search_result, &count))
		return (NULL);
	initialise_autocomp(&autocomp, &trimmed_input, &search_result, &count);
	autocomp.query_len = ft_strlen(trimmed_input);
	i = 0;
	while (paths[i])
	{
		if (search_path(paths[i], &autocomp, true) == -1)
			return (free_all_return(&search_result, &paths));
		i++;
	}
	if (count > 1 && !second_tab && !filter_matching(autocomp))
		return (free_all_return(&search_result, &paths));
	if (ft_null_array_len((void **) *(autocomp.search_results)) == 1)
		truncate_result(autocomp);
	ft_free_null_array((void **)paths);
	return (search_result);
}
