/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:21:29 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/03 15:30:11 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	cmd_test(char *const *args, t_state *state)
{
	size_t	args_len;

	(void)state;
	args_len = ft_null_array_len((void **)args);
	if (args_len == 1)
		return (1);
	if (args_len == 2)
		return (ft_strlen(args[1]) == 0);
	return (0);
}
