/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_validity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:21:28 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/11 12:04:44 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns true if the path exists.
 */
int	ft_path_has_valid_end(const char *path)
{
	struct stat		temp;

	if (lstat(path, &temp) != -1)
		return (1);
	return (0);
}

/*
 * Returns true if the path points to a link that has a valid destination or
 * if the file is not a link, returns true if the file exists.
 */
int	ft_path_has_valid_link(const char *path)
{
	struct stat		temp;

	if (stat(path, &temp) != -1)
		return (1);
	return (0);
}

/*
 * Returns true if each individual segment on the path does not exceed NAME_MAX.
 */
int	ft_path_is_within_limits(const char *path)
{
	char	**names;
	size_t	i;

	names = ft_strsplit(path, '/');
	if (!names)
		return (0);
	i = 0;
	while (names[i])
	{
		if (ft_strlen(names[i]) >= NAME_MAX)
		{
			ft_free_null_array((void **)names);
			return (0);
		}
		i++;
	}
	ft_free_null_array((void **)names);
	return (1);
}

/*
 * Normalizes the given path by handling "..", ".", and repeating slashes. The
 * normalized path will be stored inside *dst. *dst should be freed when it's
 * no longer needed.
 *
 * *dst will be set to NULL on error.
 */
void	ft_normalize_path(const char *path, char **dst)
{
	char	**split;
	char	*temp;
	size_t	i;

	*dst = NULL;
	split = ft_strsplit(path, '/');
	if (split)
		*dst = ft_strdup("/");
	i = 0;
	while (*dst && split[i])
	{
		if (ft_strequ(split[i], "..")
			&& ft_strchr(*dst, '/') != ft_strrchr(*dst, '/'))
			temp = ft_get_path_parent(*dst);
		else if (ft_strequ(split[i], ".."))
			temp = ft_strdup("/");
		else if (!ft_strequ(split[i], ".") && !ft_strequ(split[i], ""))
			ft_path_join(*dst, split[i], &temp);
		else
			ft_path_join(*dst, "", &temp);
		free(*dst);
		*dst = temp;
		i++;
	}
	ft_free_null_array((void **)split);
}
