/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:37:52 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/15 16:15:54 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	print_exit_error(char *const *args, t_state *state)
{
	ft_dprintf(STDERR_FILENO, "exit\n");
	state->exit_return_value = 255;
	return (print_error(0, ERRTEMPLATE_DOUBLE_NAMED, "exit", args[1],
			ERR_NUMERIC_ARG));
}

int	cmd_exit(char *const *args, t_state *state)
{
	unsigned long	ret;
	unsigned char	val;

	state->exit_builtin = true;
	state->exiting = 1;
	state->exit_return_value = 0;
	if (args[1])
	{
		ret = ft_atoull(args[1]);
		if (!ft_isdigit_str(args[1]) || ft_strlen(args[1]) > 19
			|| ret > LONG_MAX)
			return (print_exit_error(args, state));
		val = (unsigned char)ret;
		state->exit_return_value = (int)val;
	}
	ft_dprintf(STDERR_FILENO, "exit\n");
	return (0);
}
