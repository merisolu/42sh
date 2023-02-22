/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:27:43 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/22 11:58:56 by amann            ###   ########.fr       */
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

static int	construct_path(char *target, char **result, t_state *state, \
		bool p_flag)
{
	char	*path;

	path = NULL;
	if (ft_path_is_absolute(target))
	{
		*result = ft_strdup(target);
		if (!(*result))
			return (print_error(0, ERRTEMPLATE_NAMED, "cd", ERR_MALLOC_FAIL));
	}
	else
	{
		if (!p_flag)
			path = ft_strdup(var_get("PWD", state));
		if (!path || p_flag)
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

static int	change_directory(bool p_flag, char *path, char *target, \
		t_state *state)
{
	int		return_value;
	char	buff[PATH_MAX];

	if (!p_flag)
		ft_normalize_path(path, &target);
	else
		target = ft_strdup(path);
	return_value = chdir(target);
	if (p_flag)
	{
		if (!getcwd(buff, PATH_MAX))
			return (print_error(1, ERRTEMPLATE_DOUBLE_NAMED,
					"cd", target, ERR_MALLOC_FAIL));
		env_set("PWD", buff, &(state->env));
	}
	else
		env_set("PWD", target, &(state->env));
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

	target = get_cd_target(args, state, &p_flag);
	if (!target)
		return (1);
	if (!ft_path_is_within_limits(target)
		|| !construct_path(target, &path, state, p_flag))
		return (print_error(1, ERRTEMPLATE_DOUBLE_NAMED,
				"cd", target, ERR_INVALID_PATH));
	if (check_destination_errors(target, path) != 0)
	{
		free(path);
		return (1);
	}
	if (var_get("PWD", state))
		env_set("OLDPWD", var_get("PWD", state), &(state->env));
	return_value = change_directory(p_flag, path, target, state);
	return (return_value);
}
