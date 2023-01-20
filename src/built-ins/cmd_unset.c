/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:52:32 by amann             #+#    #+#             */
/*   Updated: 2023/01/17 16:52:40 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

/*
 * Removes the named variable. If it has been exported, it is also removed
 * from the environment and exported variables array. As with export, if
 * multiple args are passed, these are processed in a loop.
 *
 * Before deleting anything, we check that the arg passed is a vaid name.
 *
 * In accordance with POSIX, if the named variable cannot be found, this is
 * NOT treated as an error.
 *
 * In accordance with the 42sh project requirements, no options are handled.
 *
 * Simples.
 */

int	cmd_unset(char *const *args, t_state *state)
{
	int		i;
	int		ret;
	char	*name;

	ret = 0;
	i = 1;
	while (args[i])
	{
		name = args[i];
		if (!name)
			return (ret);
		if (name[valid_env_name_length(name)])
		{
			print_error_bool(false, ERRTEMPLATE_DOUBLE_NAMED_QUOTED,
				"export", name, ERR_NOT_VALID_ID);
			ret = 1;
		}
		if (!env_unset(name, &(state->env)))
			return (0);
		delete_var(name, &(state->exported));
		delete_var(name, &(state->intern));
		i++;
	}
	return (check_path_change(args, state, ret, true));
}
