/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:16:26 by amann             #+#    #+#             */
/*   Updated: 2023/03/27 16:13:27 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static bool	search_builtins(t_auto *ac)
{
	const t_cmd_dispatch	*builtins;
	size_t					i;

	builtins = get_built_in_dispatch();
	i = 0;
	while (builtins[i].run != NULL)
	{
		if (ft_strnequ(ac->query, builtins[i].name, ac->query_len))
		{
			(ac->search_result)[ac->count] = ft_strdup(
					(char *)builtins[i].name
					);
			if (!((ac->search_result)[ac->count]))
				return (print_error_bool(
						false,
						ERRTEMPLATE_SIMPLE,
						ERR_MALLOC_FAIL
					));
			(ac->count)++;
		}
		i++;
	}
	return (true);
}

static char	*get_paths(t_state *state)
{
	char	*path_var;

	path_var = env_get("PATH", state->env);
	if (!path_var)
		path_var = env_get("PATH", state->intern);
	if (!path_var)
		return (NULL);
	return (ft_strsplit(path_var, ':'));
}

static bool	search_paths_loop(char **paths, t_auto *autocomp)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (directory_search(paths[i], autocomp, true, false) == -1)
			return (false);
		i++;
	}
	return (true);
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

void	search_commands(t_auto *autocomp, t_state *state)
{
	char	**paths;

	paths = get_paths(state);
	autocomp->search_result = (char **)ft_memalloc(
			sizeof(char *) * INPUT_MAX_SIZE
			);
	if (!(paths) || !(autocomp->search_result))
	{
		ft_free_null_array((void **)paths);
		print_error(0, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL);
		return ;
	}
	autocomp->query = find_query(autocomp->trimmed_input, ' ', state, true);
	autocomp->query_len = ft_strlen(autocomp->query);
	if (!search_builtins(autocomp))
		return ;
	if (!search_paths_loop(paths, autocomp))
	{
		ft_free_null_array((void **)paths);
		return ;
	}
	ft_free_null_array((void **)(paths));
	return ;
}
