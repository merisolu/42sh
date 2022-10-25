/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:39:02 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/25 13:28:38 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_path_validity(char *path)
{
	if (ft_is_dir(path))
		return (print_named_error(path, ERR_IS_DIR, RETURN_NO_ACCESS));
	else if (path[ft_strlen(path) - 1] == '/')
		return (print_named_error(path, ERR_IS_NOT_DIR, RETURN_NO_ACCESS));
	else if (!ft_path_has_valid_end(path))
		return (print_named_error(
				path, ERR_NO_SUCH_FILE_OR_DIR, RETURN_COMMAND_NOT_FOUND)
		);
	return (0);
}

pid_t	execute(char *const *args, char *const **env, t_pipes *pipes)
{
	char	*path;
	int		return_value;

	if (!args || !(args[0]) || !env_set("_", args[0], env))
		return (print_error(ERR_MALLOC_FAIL, -1));
	// if (access(path, X_OK) == -1)
	// 	return (print_named_error(
	// 			(char *)path, ERR_NO_PERMISSION, RETURN_NO_ACCESS
	// 		));
	// if (get_built_in(args[0]))
	// 	return (run_built_in(get_built_in(args[0]), args, state));
	if (ft_strchr(args[0], '/') || (args[0][0] == '.'))
	{
		return_value = check_path_validity(args[0]);
		if (return_value != 0)
			return (return_value);
		return (bin_execute(args[0], (char **)args, *env, pipes));
	}
	return_value = bin_env_find(args[0], *env, &path);
	if (return_value == 0)
		return (print_named_error(
				args[0], ERR_COM_NOT_FOUND, RETURN_COMMAND_NOT_FOUND));
	else if (return_value == -1)
		return (return_value);
	return_value = env_set("_", path, env);
	if (return_value)
		return_value = bin_execute(path, (char **)args, *env, pipes);
	free(path);
	return (return_value);
}
