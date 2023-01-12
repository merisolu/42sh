/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:16:26 by amann             #+#    #+#             */
/*   Updated: 2023/01/12 13:27:50 by amann            ###   ########.fr       */
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

size_t	find_longest(char **search_results)
{
	size_t	max;
	size_t	current_len;
	size_t	i;

	max = 0;
	i = 0;
	while (search_results[i])
	{
		current_len = ft_strlen(search_results[i]);
		if (current_len > max)
			max = current_len;
		i++;
	}
	return (max);
}

bool	check_results_matching(t_auto autocomp)
{
	size_t	idx;
	size_t	i;
	size_t	max_len;
	char	*new_string;
	char	c;
	bool	flag;

	max_len = find_longest(*(autocomp.search_results));
	new_string = ft_strnew(max_len);
	ft_strcpy(new_string, *(autocomp.query));
	flag = false;
	i = autocomp.query_len;
	while (i < max_len)
	{
		idx = 0;
		c = (*(autocomp.search_results))[idx][i];
		while ((*(autocomp.search_results))[idx])
		{
			if ((*(autocomp.search_results))[idx][i] != c)
			{
				flag = true;
				break ;
			}
			else
				idx++;
		}
		if (flag && i == autocomp.query_len)
			return (false);
		else if (flag)
			break ;
		new_string[i] = c;
		i++;
	}
	ft_free_null_array((void **)*(autocomp.search_results));
	*(autocomp.search_results) = (char **) ft_memalloc(sizeof(char *) * 2);
	(*(autocomp.search_results))[0] = new_string;
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
	if (count > 1 && !second_tab && !check_results_matching(autocomp))
		return (free_all_return(&search_result, &paths));
	ft_free_null_array((void **)paths);
	return (search_result);
}
