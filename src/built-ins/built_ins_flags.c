/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:51:52 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/17 15:51:55 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static bool	parse_argument(char *argument, char *valid, char *found, \
t_arg_parse_error *on_error)
{
	size_t	i;

	i = 1;
	while (argument[i])
	{
		if (!ft_strchr(valid, argument[i]))
		{
			(*on_error)(argument[i]);
			return (false);
		}
		if (!ft_strchr(found, argument[i]))
			found[ft_strlen(found)] = argument[i];
		i++;
	}
	return (true);
}

int	parse_flags(char *const *args, char *valid, char *found, \
t_arg_parse_error *on_error)
{
	int	i;

	ft_bzero(found, sizeof(char) * ft_strlen(valid) + 1);
	i = 0;
	while (args[i])
	{
		if (args[i][0] != '-')
			return (i);
		if (!parse_argument(args[i], valid, found, on_error))
			return (-1);
		i++;
	}
	return (i);
}
