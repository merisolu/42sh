/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:21:29 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/06 11:12:10 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	cmd_test(char *const *args, t_state *state)
{
	size_t	args_len;
	int		invert;

	(void)state;
	args_len = ft_null_array_len((void **)args);
	if (args_len == 1)
		return (1);
	if (args_len == 2)
		return (ft_strlen(args[1]) == 0);
	invert = ft_strequ(args[1], "!");
	if (args_len == 3)
	{
		if (invert)
			return (ft_strlen(args[2]) != 0);
		return (ft_strlen(args[2]) == 0);
	}
	return (0);
}
