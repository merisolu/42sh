/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:24:10 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/30 14:34:55 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	cmd_unsetenv(char *const *args, t_state *state)
{
	char	*name;

	name = args[1];
	if (!name)
		return (print_error(0, ETEMPLATE_SHELL_NAMED,
				"unsetenv", ERR_TOO_FEW_ARGS));
	env_unset(name, &(state->env));
	return (0);
}
