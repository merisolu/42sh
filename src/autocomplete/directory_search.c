/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:19:04 by amann             #+#    #+#             */
/*   Updated: 2023/03/24 15:31:01 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

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

int	directory_search(char *path, t_auto *autocomp, bool bin, bool exec)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(path);
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry)
	{
		if (bin && !exec && bin_search(path, autocomp, entry, dir) == -1)
			return (-1);
		else if (!bin && !exec && fp_search(path, autocomp, entry, dir) == -1)
			return (-1);
		else if (!bin && exec && exec_search(path, autocomp, entry, dir) == -1)
			return (-1);
		if (autocomp->count >= INPUT_MAX_SIZE - 1)
			break ;
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}
