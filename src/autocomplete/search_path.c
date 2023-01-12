/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:19:04 by amann             #+#    #+#             */
/*   Updated: 2023/01/12 14:43:43 by amann            ###   ########.fr       */
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

static int	bin_search(char *path, t_auto *autocomp, struct dirent *entry, DIR *dir)
{
	if (ft_strnequ(*(autocomp->query), entry->d_name, autocomp->query_len)
		&& check_execution_rights(path, entry->d_name) == 1
		&& check_match_is_file(path, entry->d_name) == 1)
	{
		(*(autocomp->search_results))[*(autocomp->count)] = ft_strdup(entry->d_name);
		if (!(*(autocomp->search_results))[*(autocomp->count)])
		{
			closedir(dir);
			return (print_error(-1, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
		}
		(*(autocomp->count))++;
	}
	return (0);
}

static int	file_path_search(t_auto *autocomp, struct dirent *entry, DIR *dir)
{
	if (ft_strnequ(*(autocomp->query), entry->d_name, autocomp->query_len))
//		&& check_execution_rights(path, entry->d_name) == 1)
	{
		if (autocomp->query_len == 0
			&& (ft_strequ(entry->d_name, ".") ||  ft_strequ(entry->d_name, "..")))
			return (0);
		(*(autocomp->search_results))[*(autocomp->count)] = ft_strdup(entry->d_name);
		//if the result is a dir, we need to append a /
		if (!(*(autocomp->search_results))[*(autocomp->count)])
		{
			closedir(dir);
			return (print_error(-1, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
		}
		(*(autocomp->count))++;
	}
	return (0);
}

/*
 * Searches the specific path for an executable file with a name matching
 * partial_name. The resulting file name will be appended to the search_results
 * array. The count variable is passed by address because it will need to be
 * updated globally as this tracks the number of search results found and
 * therefore the index in the array each new result will need to be appended
 * to.
 *
 * The bin bool determines whether or not we are searching for a command,
 * and therefore only interested in files, not directories. However, if we
 * are looking for filepath, we do not need to check this.
 */

int	search_path(char *path, t_auto *autocomp, bool bin)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(path);
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry)
	{
		if (bin && bin_search(path, autocomp, entry, dir) == -1)
			return (-1);
		else if (!bin && file_path_search(autocomp, entry, dir) == -1)
			return (-1);
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}
