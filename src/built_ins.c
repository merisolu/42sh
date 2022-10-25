/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:18:43 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/25 14:05:44 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_cmd_dispatch	*get_built_in_dispatch(void)
{
	static const t_cmd_dispatch	dispatch_table[] = {
	{"cd", &cmd_cd},
	{"echo", &cmd_echo},
	{"env", &cmd_env},
	{"setenv", &cmd_setenv},
	{"unsetenv", &cmd_unsetenv},
	{"exit", &cmd_exit},
	{"", NULL}
	};

	return (&(dispatch_table[0]));
}

char	*search_for_built_in(const char *partial_name)
{
	const t_cmd_dispatch	*dispatch_table;
	size_t					i;

	dispatch_table = get_built_in_dispatch();
	i = 0;
	while (dispatch_table[i].run != NULL)
	{
		if (ft_strnequ(
				partial_name, dispatch_table[i].name, ft_strlen(partial_name)))
			return (ft_strdup((char *)dispatch_table[i].name));
		i++;
	}
	return (NULL);
}

t_cmd	*get_built_in(const char *name)
{
	const t_cmd_dispatch	*dispatch_table;
	size_t					i;

	dispatch_table = get_built_in_dispatch();
	i = 0;
	while (dispatch_table[i].run != NULL)
	{
		if (ft_strequ(dispatch_table[i].name, name))
			return (dispatch_table[i].run);
		i++;
	}
	return (NULL);
}

int	run_built_in(t_cmd cmd, char *const *args, t_state *state)
{
	int	return_value;

	return_value = cmd(args, state);
	set_return_value(return_value, state);
	return (return_value);
}
