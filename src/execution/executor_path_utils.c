/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:27:48 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/13 14:17:09 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
 * Returns true if a path exists, either in env or internal variables.
 *
 * Nothing fancy, but we need to check this in a couple of places.
 */

bool	path_exists(t_state *state)
{
	char	*path;

	path = var_get("PATH", state);
	if (!path)
		return (false);
	return (true);
}

/*
 * Checks whether or not the given path is OK for execution. Returns an integer
 * that can be used as a return value (0 on success > 0 on failure, with
 * specific values for specific errors).
 */

int	check_path_validity(char *path)
{
	if (ft_is_dir(path))
		return (print_error(RETURN_NO_ACCESS, ERRTEMPLATE_NAMED,
				path, ERR_IS_DIR));
	else if (path[ft_strlen(path) - 1] == '/')
		return (print_error(RETURN_NO_ACCESS, ERRTEMPLATE_NAMED,
				path, ERR_IS_NOT_DIR));
	else if (!ft_path_has_valid_end(path))
		return (print_error(RETURN_COMMAND_NOT_FOUND, ERRTEMPLATE_NAMED,
				path, ERR_NO_SUCH_FILE_OR_DIR));
	else if (access(path, X_OK) == -1)
		return (print_error(RETURN_NO_ACCESS, ERRTEMPLATE_NAMED,
				path, ERR_NO_PERMISSION));
	return (0);
}

/*
 * Attempts to find a binary with the given name from the hash table, then from
 * PATH in env. Returns -1 on malloc fail, 0 on not found in PATH, 1 on success.
 */
int	find_binary(char *name, t_state *state, char **result, bool silent)
{
	char	*hash_table_result;

	hash_table_result = hash_table_get_path(name, state->hash_table);
	if (hash_table_result && result)
	{
		*result = ft_strdup(hash_table_result);
		if (!(*result))
			return (print_error(-1, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
		return (1);
	}
	return (bin_env_find(name, state, result, silent));
}
