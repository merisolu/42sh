/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_test_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:40:11 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/06 13:18:41 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

/*
 * Returns 0 if the file type of the given path matches the given type, 1
 * otherwise. The return values are seemingly opposite of what they should be
 * to make it easier to return the value directly from cmd_test().
 */
int	cmd_test_does_file_type_match(char *path, char type)
{
	if (type == 'b')
		return (!ft_file_is_type(path, S_IFBLK));
	if (type == 'c')
		return (!ft_file_is_type(path, S_IFCHR));
	if (type == 'd')
		return (!ft_file_is_type(path, S_IFDIR));
	if (type == 'f')
		return (!ft_file_is_type(path, S_IFREG));
	if (type == 'g')
		return (!ft_file_is_type(path, S_ISGID));
	if (type == 'L')
		return (!ft_file_is_type(path, S_IFLNK));
	if (type == 'p')
		return (!ft_file_is_type(path, S_IFIFO));
	if (type == 'S')
		return (!ft_file_is_type(path, S_IFSOCK));
	if (type == 'u')
		return (!ft_file_is_type(path, S_ISUID));
	return (1);
}

/*
 * Returns 0 if the permission of the given path matches the given permission, 1
 * otherwise. The return values are seemingly opposite of what they should be
 * to make it easier to return the value directly from cmd_test().
 */
int	cmd_test_does_file_have_permission(char *path, char permission)
{
	int	mode;

	if (permission == 'r')
		mode = R_OK;
	else if (permission == 'w')
		mode = W_OK;
	else
		mode = X_OK;
	return (!(access(path, mode) == 0));
}

/*
 * Returns 0 if the file at the given path is more than zero bytes in size, 1
 * otherwise. The return values are seemingly opposite of what they should be
 * to make it easier to return the value directly from cmd_test().
 */
int	cmd_test_file_has_data(char *path)
{
	struct stat	temp;

	if (lstat(path, &temp) == -1)
		return (1);
	return (!(temp.st_size > 0));
}
