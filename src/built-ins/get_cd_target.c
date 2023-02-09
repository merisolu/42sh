/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd_target.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:43:11 by amann             #+#    #+#             */
/*   Updated: 2023/02/09 14:56:13 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static bool	check_flags(char *const *args, int *i, bool *p_flag)
{
	int	j;

	*i = 1;
	*p_flag = false;
	while (args[*i] && args[*i][0] == '-')
	{
		j = 0;
		while (args[*i][j])
		{
			*p_flag = args[*i][j] == 'P';
			if (!ft_strchr("PL-", args[*i][j])
				|| (j > 1 && args[*i][j] == '-')
				|| (j == 1 && args[*i][j] == '-' && args[*i][j + 1]))
			{
				print_error_bool(false, ERRTEMPLATE_CD, args[*i][j],
					ERR_INVALID_OPTION);
				return (print_error_bool(false, "%s\n", CD_USAGE));
			}
			j++;
		}
		(*i)++;
	}
	return (true);
}

char	*get_cd_target(char *const *args, t_state *state, bool *p_flag)
{
	char	*temp;
	int		i;

	if (!check_flags(args, &i, p_flag))
		return (NULL);
	if (ft_strequ(args[i], "--"))
		i++;
	if (!args[i])
	{
		temp = var_get("HOME", state);
		if (!temp)
			print_error(0, ERRTEMPLATE_NAMED, "cd", ERR_NO_HOME);
		return (temp);
	}
	if (ft_strequ(args[i], "-"))
	{
		temp = var_get("OLDPWD", state);
		if (!temp)
			print_error(0, ERRTEMPLATE_NAMED, "cd", ERR_NO_OLDPWD);
		if (ft_is_dir(temp))
			ft_putendl(temp);
		return (temp);
	}
	return (args[i]);
}
