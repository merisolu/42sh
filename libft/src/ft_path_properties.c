/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_properties.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:14:59 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/19 15:16:49 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns true if the given path is self (.) or parent (..);
 */
int	ft_path_is_self_or_parent(const char *path)
{
	char	*name;

	name = ft_get_path_name_ptr(path);
	return (ft_strequ(name, ".") || ft_strequ(name, "..")
		|| ft_strequ(name, "./.") || ft_strequ(name, "./.."));
}

/*
 * Returns true if the given file/directory the path points to is hidden.
 */
int	ft_is_hidden(const char *path)
{
	char	*name;

	name = ft_get_path_name_ptr(path);
	if (!name)
		return (0);
	return (name[0] == '.');
}

/*
 * Returns true if the given path is absolute.
 */
int	ft_path_is_absolute(const char *path)
{
	if (!path)
		return (0);
	return (path[0] == '/');
}
