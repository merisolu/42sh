/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:12:18 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/11 14:24:01 by amann            ###   ########.fr       */
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
	i = 1;
	no_newline = ft_strequ(args[i], "-n");
	i += no_newline;
	while (i < len)
	{
		if (write(1, args[i], ft_strlen(args[i])) == -1)
			return (print_named_error("echo", ERR_WRITE_BAD_FD, 1));
		if (i != len - 1)
			ft_putchar(' ');
		i++;
	}
	if (!no_newline)
		ft_putchar('\n');
	return (0);
}
