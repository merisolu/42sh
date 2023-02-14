/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:37:52 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/14 17:15:52 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	cmd_exit(char *const *args, t_state *state)
{
	state->exit_return_value = 0;
	if (args[1])
	{
		if (!ft_isdigit_str(args[1]) || ft_strlen(args[1]) > 10)
		{
			ft_dprintf(STDERR_FILENO, "exit\n");
			print_error(0, ERRTEMPLATE_DOUBLE_NAMED, "exit", args[1],
					ERR_NUMERIC_ARG);
			state->exit_builtin = true;
			state->exiting = 1;
			state->exit_return_value = 255;
			return (0);
		}
		state->exit_return_value = ft_atoi(args[1]);
	}
	ft_dprintf(STDERR_FILENO, "exit\n");
	state->exit_builtin = true;
	state->exiting = 1;
	return (0);
}
