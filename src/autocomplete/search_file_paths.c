/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_file_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:44:44 by amann             #+#    #+#             */
/*   Updated: 2023/02/25 14:33:21 by amann            ###   ########.fr       */
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

	if (ft_strchr(*query, '/'))
	{
		*path = ft_strndup(*query, last_slash(*query));
		temp = ft_strdup(ft_strrchr(*query, '/') + 1);
		ft_strdel(query);
		*query = temp;
		return ;
	}
	temp = getcwd(NULL, PATH_MAX);
	*path = ft_strjoin(temp, "/");
	free(temp);
	return ;
}

static bool	set_exec(char *path, char *ti)
{
	bool	first_word;
	int		i;

	first_word = true;
	i = (int)ft_strlen(path) - 1;
	while (i >= 0)
	{
		if (ti[i] == ' ')
		{
			first_word = false;
			break ;
		}
		i--;
	}
	if (first_word && path[0] == '.')
		return (true);
	return (false);
}

char	**search_file_paths(char **trimmed_input, t_auto_bools *a_bool, \
		t_state *state)
{
	char	**search_result;
	char	*query;
	int		count;
	char	*path;
	t_auto	autocomp;

	search_result = (char **) ft_memalloc(sizeof(char *) * INPUT_MAX_SIZE);
	if (!search_result)
		return (print_error_ptr(NULL, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	count = 0;
	query = find_query(*trimmed_input, ' ', state, true);
	initialise_autocomp(&autocomp, &query, &search_result, &count);
	path = NULL;
	reset_query_and_path(&query, &path);
	if (!path || !query)
		return (print_error_ptr(NULL, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	autocomp.query_len = ft_strlen(query);
	directory_search(path, &autocomp, false, set_exec(path, *trimmed_input));
	free(path);
	return (wrap_up(&autocomp, a_bool));
}
