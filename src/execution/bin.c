/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:29:06 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/30 14:07:17 by jumanner         ###   ########.fr       */
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
 * Returns 1 on success, 0 on not found, -1 on failed malloc.
 */

static int	bin_find(const char *name, char **paths, char **result)
{
	size_t	i;

	i = 0;
	if ((name[0] == '/' || ft_strnequ(name, "./", 2))
		&& ft_points_to_file(name))
	{
		*result = ft_strdup(name);
		if (!(*result))
			return (print_error(
					-1, ETEMPLATE_SHELL_SIMPLE, ERR_MALLOC_FAIL));
		return (1);
	}
	while (paths[i])
	{
		ft_path_join(paths[i], name, result);
		if (!(*result))
			return (print_error(
					-1, ETEMPLATE_SHELL_SIMPLE, ERR_MALLOC_FAIL));
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

int	bin_env_find(const char *name, char *const *env, char **result)
{
	char	*path;
	char	**paths;
	int		return_value;

	*result = NULL;
	path = env_get("PATH", env);
	if (!path)
		return (0);
	paths = ft_strsplit(path, ':');
	if (!paths)
		return (print_error(-1, ETEMPLATE_SHELL_SIMPLE, ERR_MALLOC_FAIL));
	return_value = bin_find(name, paths, result);
	ft_free_null_array((void **)paths);
	return (return_value);
}

/*
 * Attempts to fork the current process, and transform it into a new process
 * defined by the given path to a binary.
 *
 * If fork or execve calls fail, an error message is printed to stderr.
 */

pid_t	bin_execute(char *p, char **arg, char *const *env, t_ast_context *ast)
{
	pid_t	result;

	if (!p)
		return (-1);
	result = start_fork(ast);
	if (result == 0)
	{
		if (execve(p, arg, env) == -1)
			exit(print_error(
					1, ETEMPLATE_SHELL_SIMPLE, ERR_CHILD_PROC_FAIL));
	}
	return (result);
}
