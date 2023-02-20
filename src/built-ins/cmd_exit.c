/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:37:52 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/20 14:29:35 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

void	print_exit(t_state *state)
{
	if (getpid() == state->group_id)
		ft_putendl_fd("exit", STDERR_FILENO);
}

int	print_exit_error(char *const *args, t_state *state)
{
	print_exit(state);
	state->exit_return_value = 255;
	return (print_error(0, ERRTEMPLATE_DOUBLE_NAMED, "exit", args[1],
			ERR_NUMERIC_ARG));
}

int	cmd_exit(char *const *args, t_state *state)
{
	unsigned long	ret;
	unsigned char	val;

	if (ft_null_array_len((void **)args) > 2)
	{
		print_exit(state);
		return (print_error(1, ERRTEMPLATE_NAMED,
				"exit", ERR_TOO_MANY_ARGS));
	}
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
	print_exit(state);
	return (0);
}
