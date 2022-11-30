/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:27:43 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/30 14:07:17 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static int	print_cd_error(char *name, char *message, int return_value)
{
	ft_dprintf(STDERR_FILENO, "21sh: cd: ");
	if (name)
		ft_dprintf(STDERR_FILENO, "%s: ", name);
	ft_dprintf(STDERR_FILENO, "%s\n", message);
	return (return_value);
}

static int	check_destination_errors(char *name, char *path)
{
	if (ft_points_to_file(path))
		return (print_cd_error(name, ERR_IS_NOT_DIR, 1));
	if (!ft_points_to_dir(path))
		return (print_cd_error(name, ERR_NO_SUCH_FILE_OR_DIR, 1));
	if (!ft_path_is_within_limits(path))
		return (print_cd_error(name, ERR_INVALID_PATH, 1));
	if (access(path, X_OK) != 0)
		return (print_cd_error(name, ERR_NO_PERMISSION, 1));
	return (0);
}

static char	*get_target(char *const *args, size_t count, char *const *env)
{
	char	*temp;

	if (count <= 1 || (count == 2 && ft_strequ(args[1], "--")))
	{
		temp = env_get("HOME", env);
		if (!temp)
			print_cd_error(NULL, ERR_NO_HOME, 0);
		return (temp);
	}
	else
	{
		if (ft_strequ(args[1], "-"))
		{
			temp = env_get("OLDPWD", env);
			if (!temp)
				print_cd_error(NULL, ERR_NO_OLDPWD, 0);
			if (ft_is_dir(temp))
				ft_putendl(temp);
			return (temp);
		}
	}
	if (count > 2 && ft_strequ(args[1], "--"))
		return (args[2]);
	return (args[1]);
}

static int	construct_path(char *target, char **result)
{
	char	*path;

	if (ft_path_is_absolute(target))
	{
		*result = ft_strdup(target);
		if (!(*result))
			return (print_error(0, ERR_MALLOC_FAIL));
	}
	else
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (print_error(0, ERR_CANNOT_GET_CWD));
		ft_path_join(path, target, result);
		free(path);
		if (!(*result))
			return (print_error(0, ERR_MALLOC_FAIL));
	}
	return (1);
}

int	cmd_cd(char *const *args, t_state *state)
{
	char	*target;
	char	*path;
	size_t	arg_count;
	int		return_value;

	arg_count = ft_null_array_len((void **)args);
	target = get_target(args, arg_count, state->env);
	if (!target)
		return (1);
	if (!ft_path_is_within_limits(target) || !construct_path(target, &path))
		return (print_cd_error(target, ERR_INVALID_PATH, 1));
	return_value = check_destination_errors(target, path);
	if (return_value != 0)
	{
		free(path);
		return (return_value);
	}
	if (env_get("PWD", state->env))
		env_set("OLDPWD", env_get("PWD", state->env), &(state->env));
	ft_normalize_path(path, &target);
	env_set("PWD", target, &(state->env));
	return_value = chdir(target);
	free(target);
	free(path);
	return (return_value);
}
