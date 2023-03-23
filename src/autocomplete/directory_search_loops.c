/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_search_loops.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:56:14 by amann             #+#    #+#             */
/*   Updated: 2023/03/23 13:08:14 by amann            ###   ########.fr       */
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

int	exec_search(char *path, t_auto *ac, struct dirent *entry, DIR *dir)
{
	if (ft_strnequ(*(ac->query), entry->d_name, ac->query_len)
		&& check_execution_rights(path, entry->d_name) == 1)
	{
		if (ac->query_len == 0
			&& (ft_strequ(entry->d_name, ".")
				|| ft_strequ(entry->d_name, "..")))
			return (0);
		(*(ac->search_results))[(ac->count)] = ft_strdup(entry->d_name);
		if (!(*(ac->search_results))[(ac->count)])
		{
			closedir(dir);
			return (print_error(-1, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
		}
		if (!check_result_is_dir(path, ac, entry, dir))
			return (-1);
		((ac->count))++;
	}
	return (0);
}

int	bin_search(char *path, t_auto *ac, struct dirent *entry, DIR *dir)
{
	if (ft_strnequ(*(ac->query), entry->d_name, ac->query_len)
		&& check_execution_rights(path, entry->d_name) == 1
		&& check_match_is_file(path, entry->d_name) == 1)
	{
		(*(ac->search_results))[(ac->count)] = ft_strdup(entry->d_name);
		if (!(*(ac->search_results))[(ac->count)])
		{
			closedir(dir);
			return (print_error(-1, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
		}
		((ac->count))++;
	}
	return (0);
}

int	fp_search(char *path, t_auto *ac, struct dirent *entry, DIR *dir)
{
	if (ft_strnequ(*(ac->query), entry->d_name, ac->query_len))
	{
		if (ac->query_len == 0
			&& (ft_strequ(entry->d_name, ".")
				|| ft_strequ(entry->d_name, "..")))
			return (0);
		(*(ac->search_results))[(ac->count)] = ft_strdup(entry->d_name);
		if (!(*(ac->search_results))[(ac->count)])
		{
			closedir(dir);
			return (print_error(-1, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
		}
		if (!check_result_is_dir(path, ac, entry, dir))
			return (-1);
		((ac->count))++;
	}
	return (0);
}
