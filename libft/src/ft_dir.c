/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:56:11 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/30 13:36:36 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns true if the given path is a directory. False otherwise.
 */
int	ft_is_dir(const char *path)
{
	struct stat		temp;

	if (lstat(path, &temp) == -1)
		return (0);
	else if ((temp.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}

/*
 * Returns true if the given path points to a directory. False otherwise.
 */
int	ft_points_to_dir(const char *path)
{
	struct stat		temp;

	if (stat(path, &temp) == -1)
		return (0);
	else if ((temp.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}
