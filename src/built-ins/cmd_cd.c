/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:27:43 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/09 14:44:57 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static int	check_destination_errors(char *name, char *path)
{
	if (ft_points_to_file(path))
		return (print_error(1, ERRTEMPLATE_DOUBLE_NAMED,
				"cd", name, ERR_IS_NOT_DIR));
	if (!ft_points_to_dir(path))
		return (print_error(1, ERRTEMPLATE_DOUBLE_NAMED,
				"cd", name, ERR_NO_SUCH_FILE_OR_DIR));
	if (!ft_path_is_within_limits(path))
		return (print_error(1, ERRTEMPLATE_DOUBLE_NAMED,
				"cd", name, ERR_INVALID_PATH));
	if (access(path, X_OK) != 0)
		return (print_error(1, ERRTEMPLATE_DOUBLE_NAMED,
				"cd", name, ERR_NO_PERMISSION));
	return (0);
}

static int	construct_path(char *target, char **result)
{
	char	*path;

	if (ft_path_is_absolute(target))
	{
		*result = ft_strdup(target);
		if (!(*result))
			return (print_error(0, ERRTEMPLATE_NAMED, "cd", ERR_MALLOC_FAIL));
	}
	else
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (print_error(0,
					ERRTEMPLATE_NAMED, "cd", ERR_CANNOT_GET_CWD));
		ft_path_join(path, target, result);
		free(path);
		if (!(*result))
			return (print_error(0, ERRTEMPLATE_NAMED, "cd", ERR_MALLOC_FAIL));
	}
	return (1);
}

static int	change_directory(bool p_flag, char *path, char *target)
{
	int	return_value;

	if (!p_flag)
		ft_normalize_path(path, &target);
	else
		target = ft_strdup(path);
	return_value = chdir(target);
	free(target);
	free(path);
	return (return_value);
}

int	cmd_cd(char *const *args, t_state *state)
{
	char	*target;
	char	*path;
	int		return_value;
	bool	p_flag;
	char	buff[PATH_MAX];

	target = get_cd_target(args, state, &p_flag);
	if (!target)
		return (1);
	if (!ft_path_is_within_limits(target) || !construct_path(target, &path))
		return (print_error(1, ERRTEMPLATE_DOUBLE_NAMED,
				"cd", target, ERR_INVALID_PATH));
	if (check_destination_errors(target, path) != 0)
	{
		free(path);
		return (1);
	}
	if (var_get("PWD", state))
		env_set("OLDPWD", var_get("PWD", state), &(state->env));
	return_value = change_directory(p_flag, path, target);
	getcwd(buff, PATH_MAX);
	env_set("PWD", buff, &(state->env));
	return (return_value);
}
