/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:53:19 by amann             #+#    #+#             */
/*   Updated: 2023/02/17 15:26:33 by jumanner         ###   ########.fr       */
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

static void	print_env(char *const *env, char *const *deny_list)
{
	size_t	i;
	size_t	o;
	bool	can_print;

	i = 0;
	while ((env)[i])
	{
		can_print = true;
		o = 0;
		while (deny_list && deny_list[o])
		{
			can_print = !ft_strequ((env)[i], deny_list[o]);
			if (!can_print)
				break ;
			o++;
		}
		if (can_print)
			ft_putendl((env)[i]);
		i++;
	}
}

int	cmd_set(char *const *args, t_state *state)
{
	(void) args;
	if (!(state->intern) || !(state->env))
		return (0);
	print_env(state->env, NULL);
	print_env(state->intern, state->env);
	return (0);
}
