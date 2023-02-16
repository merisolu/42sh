/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:53:19 by amann             #+#    #+#             */
/*   Updated: 2023/02/16 17:24:30 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

/*
 * The command set prints out the internal variables of the shell.
 *
 * The POSIX standard would require a number of flags to be handled:
 * https://pubs.opengroup.org/onlinepubs/009695399/utilities/set.html
 *
 * However, for the purposes of this project, printing the variables is
 * sufficient.
 */

static void	print_env(char *const *env)
{
	size_t	i;

	i = 0;
	while ((env)[i])
	{
		ft_putendl((env)[i]);
		i++;
	}
}

int	cmd_set(char *const *args, t_state *state)
{
	(void) args;
	if (!(state->intern) || !(state->env))
		return (0);
	print_env(state->env);
	print_env(state->intern);
	return (0);
}
