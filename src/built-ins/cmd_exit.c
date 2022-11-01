/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:37:52 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 14:14:28 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	cmd_exit(char *const *args, t_state *state)
{
	state->exit_return_value = 0;
	if (args[1])
		state->exit_return_value = ft_atoi(args[1]);
	state->exiting = 1;
	return (0);
}
