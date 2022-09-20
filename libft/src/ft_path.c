/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:02:51 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/19 15:31:54 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Joins two paths together, and puts the result into dst. If the allocation
 * fails, *dst will be NULL.
 */
void	ft_path_join(const char *a, const char *b, char **dst)
{
	int		trailing_slash;

	if (!dst)
		return ;
	trailing_slash = a[ft_strlen(a) - 1] == '/';
	*dst = ft_strnew(ft_strlen(a) + ft_strlen(b) + !trailing_slash);
	if (!(*dst))
		return ;
	ft_strcat(*dst, a);
	if (!trailing_slash)
		(*dst)[ft_strlen(*dst)] = '/';
	ft_strcat(*dst + ft_strlen(*dst), b);
}

/*
 * Returns a pointer to the last named section of the path.
 * Returns null on failure.
 */
char	*ft_get_path_name_ptr(const char *path)
{
	char	*result;

	if (!path)
		return (NULL);
	result = ft_strrchr(path, '/');
	if (!result)
		return ((char *)path);
	return (result + 1);
}

/*
 * Returns a dynamically allocated string which contains the path of the parent
 * directory of the given path. Returns NULL on error.
 */
char	*ft_get_path_parent(const char *path)
{
	if ((size_t)(ft_strrchr(path, '/') - path) > 0)
		return (ft_strsub(path, 0, (size_t)(ft_strrchr(path, '/') - path)));
	return (ft_strdup("/"));
}
