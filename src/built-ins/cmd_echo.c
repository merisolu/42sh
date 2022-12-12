/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:12:18 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/12 13:52:06 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	cmd_echo(char *const *args, t_state *state)
{
	int		no_newline;
	size_t	len;
	size_t	i;

	(void)state;
	len = ft_null_array_len((void **)args);
	no_newline = ft_strequ(args[1], "-n");
	i = no_newline + 1;
	while (i < len)
	{
		if (write(1, args[i], ft_strlen(args[i])) == -1)
			return (print_error(1, ETEMPLATE_SHELL_NAMED,
					"echo", ERR_WRITE_BAD_FD));
		if (i != len - 1)
			ft_putchar(' ');
		i++;
	}
	if (!no_newline)
	{
		if (write(1, "\n", 1) == -1)
			return (print_error(1, ETEMPLATE_SHELL_NAMED,
					"echo", ERR_WRITE_BAD_FD));
	}
	return (0);
}
