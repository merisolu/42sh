/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:29:06 by jumanner          #+#    #+#             */
/*   Updated: 2023/10/10 15:53:47 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
 * Attempts to find the given binary from all given paths, the local directory
 * if the name beings with "./", and the absolute path if the name begins with
 * a slash.
 *
 * If the binary was found its path will be stored in result. If nothing was
 * found, the result will be NULL.
 *
 * *result should be freed after it is no longer needed.
 *
 * Returns 1 on success, 0 on not found in PATH, -1 on failed malloc.
 */
static int	bin_find(const char *name, char **paths, char **result)
{
	size_t	i;

	i = 0;
	if ((ft_strnequ(name, "/", 1) || ft_strnequ(name, "./", 2))
		&& ft_points_to_file(name))
	{
		*result = ft_strdup(name);
		if (!(*result))
			return (print_error(
					-1, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
		return (1);
	}
	while (paths[i])
	{
		ft_path_join(paths[i], name, result);
		if (!(*result))
			return (print_error(
					-1, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
		if (ft_points_to_file(*result))
			return (1);
		ft_memdel((void **)result);
		i++;
	}
	*result = NULL;
	return (0);
}

/*
 * Attempts to find the given binary from all paths in the given environment,
 * or if an absolute path was passed directly from the given path.
 *
 * If the binary was found its path will be stored in result. If nothing was
 * found, the result will be empty.
 *
 * Returns 1 on success, 0 on not found, -1 on malloc failure.
 */

int	bin_env_find(const char *name, t_state *state, char **result, bool silent)
{
	char	*path;
	char	**paths;
	int		return_value;

	*result = NULL;
	path = var_get("PATH", state);
	if (!path || ft_strlen(path) == 0)
	{
		if (silent)
			return (-1);
		return (print_error(RETURN_COMMAND_NOT_FOUND,
				ERRTEMPLATE_SIMPLE, ERR_NO_SUCH_FILE_OR_DIR));
	}
	paths = ft_strsplit(path, ':');
	if (!paths)
	{
		if (silent)
			return (-1);
		return (print_error(-1, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	}
	return_value = bin_find(name, paths, result);
	ft_free_null_array((void **)paths);
	return (return_value);
}

/*
 * Attempts to execve the current process into a new process defined by the
 * given path to a binary.
 *
 * If the execve call fails, an error message is printed to stderr and the
 * process exits.
 */

void	bin_execve(char *path, char **arg, char *const *env)
{
	if (execve(path, arg, env) == -1)
		exit(print_error(
				1, ERRTEMPLATE_SIMPLE, ERR_CHILD_PROC_FAIL));
}
