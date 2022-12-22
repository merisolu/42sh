/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:48:06 by amann             #+#    #+#             */
/*   Updated: 2022/12/22 15:04:03 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static bool	setup_var_arrays(t_state *state)
{
	if (!(state->exported))
		state->exported = (char **) ft_memalloc(sizeof(char *) * (INPUT_MAX_SIZE / 2));
	if (!(state->intern))
		state->intern = (char **) ft_memalloc(sizeof(char *) * (INPUT_MAX_SIZE / 2));
	if (!(state->intern) || !(state->exported))
		return (print_error(false, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	return (true);
}

/*
 * export works similarly to setenv; ostensibly it allows the user to declare
 * variables that will be permanently added to the environment of future
 * commands.
 *
 * With the format:
 *
 * export <name>=<value>
 *
 * The variable is created added to the internal shell variables and
 * the environment. If <name> already exists, it is updated with the new value.
 *
 * With the format:
 *
 * export <name>
 *
 * If <name> exists in the internal shell variables, it will be exported to
 * the environment.
 *
 * If it does not exist, it will not go into the env, but will go into the list
 * of exported variables (assuming the syntax is ok) UNLESS that variable
 * already exists.
 *
 * When the -p flag is specified, all of the names of exported variables are
 * written to the stdout.
 */

int	cmd_export(char *const *args, t_state *state)
{
	if (!args[1] || (ft_strequ(args[1], "-p") && !args[2]))
	{
		env_print_all(state->exported);
		return (1);
	}
	if (!setup_var_arrays(state))
		return (0);
	return (1);
}
