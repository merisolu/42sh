/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:39:02 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/15 16:06:29 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

static int	find_path(char *const *args, t_state *state, char **path)
{
	int		return_value;

	return_value = bin_env_find(args[0], state->env, path);
	if (return_value == 0)
		return (print_named_error(
				args[0], ERR_COM_NOT_FOUND, RETURN_COMMAND_NOT_FOUND));
	else if (return_value == -1)
		return (return_value);
	return (1);
}

static int	execute_absolute_path(char *const *args, t_state *state, \
t_ast_execution *ast)
{
	int	return_value;

	return_value = check_path_validity(args[0]);
	if (return_value != 0)
		return (return_value);
	return (bin_execute(args[0], (char **)args, state->env, ast));
}

pid_t	execute(char *const *args, t_state *state, t_ast_execution *ast)
{
	char	*path;
	int		return_value;

	if (built_in_get(args[0]))
		return (built_in_run(built_in_get(args[0]), args, state, ast));
	if (ft_strchr(args[0], '/') || (args[0][0] == '.'))
		return (execute_absolute_path(args, state, ast));
	return_value = find_path(args, state, &path);
	if (return_value != 1)
		return (return_value);
	if (access(path, X_OK) == -1)
		return (print_named_error(
				(char *)path, ERR_NO_PERMISSION, RETURN_NO_ACCESS
			));
	return_value = env_set("_", path, &(state->env));
	if (return_value)
		return_value = bin_execute(path, (char **)args, state->env, ast);
	free(path);
	return (return_value);
}
