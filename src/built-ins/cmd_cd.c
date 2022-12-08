/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:27:43 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/08 15:29:29 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static int	check_destination_errors(char *name, char *path)
{
	if (ft_points_to_file(path))
		return (print_error(1, ETEMPLATE_SHELL_DOUBLE_NAMED,
				"cd", name, ERR_IS_NOT_DIR));
	if (!ft_points_to_dir(path))
		return (print_error(1, ETEMPLATE_SHELL_DOUBLE_NAMED,
				"cd", name, ERR_NO_SUCH_FILE_OR_DIR));
	if (!ft_path_is_within_limits(path))
		return (print_error(1, ETEMPLATE_SHELL_DOUBLE_NAMED,
				"cd", name, ERR_INVALID_PATH));
	if (access(path, X_OK) != 0)
		return (print_error(1, ETEMPLATE_SHELL_DOUBLE_NAMED,
				"cd", name, ERR_NO_PERMISSION));
	return (0);
}

static char	*get_target(char *const *args, size_t count, char *const *env)
{
	char	*temp;

	if (count <= 1 || (count == 2 && ft_strequ(args[1], "--")))
	{
		temp = env_get("HOME", env);
		if (!temp)
			print_error(0, ETEMPLATE_SHELL_NAMED, "cd", ERR_NO_HOME);
		return (temp);
	}
	else
	{
		if (ft_strequ(args[1], "-"))
		{
			temp = env_get("OLDPWD", env);
			if (!temp)
				print_error(0, ETEMPLATE_SHELL_NAMED, "cd", ERR_NO_OLDPWD);
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
			return (print_error(0, ETEMPLATE_SHELL_NAMED, "cd", ERR_MALLOC_FAIL));
	}
	else
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (print_error(0, ETEMPLATE_SHELL_NAMED, "cd", ERR_CANNOT_GET_CWD));
		ft_path_join(path, target, result);
		free(path);
		if (!(*result))
			return (print_error(0, ETEMPLATE_SHELL_NAMED, "cd", ERR_MALLOC_FAIL));
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
		return (print_error(1, ETEMPLATE_SHELL_DOUBLE_NAMED,
				"cd", target, ERR_INVALID_PATH));
	if (check_destination_errors(target, path) != 0)
	{
		free(path);
		return (1);
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
