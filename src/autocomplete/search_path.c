/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:19:04 by amann             #+#    #+#             */
/*   Updated: 2023/01/11 14:32:07 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static int	check_execution_rights(char *path, char *name)
{
	int		result;
	char	*temp;

	ft_path_join(path, name, &temp);
	if (!temp)
		return (-1);
	result = (access(temp, X_OK) == 0);
	free(temp);
	return (result);
}

static int	check_match_is_file(char *path, char *name)
{
	int		result;
	char	*temp;

	ft_path_join(path, name, &temp);
	if (!temp)
		return (-1);
	result = (ft_is_file(temp) || ft_points_to_file(temp));
	free(temp);
	return (result);
}

/*
 * Searches the specific path for an executable file with a name matching
 * partial_name. The resulting file name will be appended to the search_results
 * array. The count variable is passed by address because it will need to be
 * updated globally as this tracks the number of search results found and
 * therefore the index in the array each new result will need to be appended
 * to.
 */

int	search_path(char *path, char *query, char ***search_results, int *count)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(path);
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry)
	{
		if (ft_strnequ(query, entry->d_name, ft_strlen(query))
			&& check_execution_rights(path, entry->d_name) == 1
			&& check_match_is_file(path, entry->d_name) == 1)
		{
			(*search_results)[*count] = ft_strdup(entry->d_name);
			if (!(*search_results)[*count])
			{
				closedir(dir);
				return (print_error(-1, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
			}
			(*count)++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}
