/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_result_is_dir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:05:12 by amann             #+#    #+#             */
/*   Updated: 2023/03/24 17:48:06 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static bool close_and_return(DIR *dir)
{
	closedir(dir);
	return (print_error_bool(false, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
}

bool check_result_is_dir(char *path, t_auto *autocomp,
						 struct dirent *entry, DIR *dir)
{
	char *temp;
	char *full_path;

	full_path = ft_strjoin(path, entry->d_name);
	if (!full_path)
		return (close_and_return(dir));
	if (ft_is_dir(full_path))
	{
		temp = ft_strnew(sizeof(char) + (ft_strlen(entry->d_name) + 1));
		if (!temp)
		{
			free(full_path);
			return (close_and_return(dir));
		}
		ft_strcpy(temp, entry->d_name);
		temp[ft_strlen(entry->d_name)] = '/';
		ft_strdel(&((autocomp->search_result)[autocomp->count]));
		(autocomp->search_result)[autocomp->count] = temp;
	}
	free(full_path);
	return (true);
}
