/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:02:23 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/14 14:53:28 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static int	parse_flag(char *arg, char *valid, char *found,
t_arg_parse_error *on_error)
{
	int	o;

	o = 1;
	while (arg[o])
	{
		if (!ft_strchr(valid, arg[o]))
		{
			if (o == 1 && ft_isdigit(arg[o]))
				return (1);
			(*on_error)(arg[o]);
			return (-1);
		}
		if (!ft_strchr(found, arg[o]))
			found[ft_strlen(found)] = arg[o];
		o++;
	}
	return (0);
}

int	cmd_fc_parse_flags(char *const *args, char *valid, char *found,
t_arg_parse_error *on_error)
{
	int	i;
	int	flag_parse_result;

	ft_bzero(found, sizeof(char) * ft_strlen(valid));
	i = 0;
	while (args[i])
	{
		if (args[i][0] != '-')
			return (i);
		flag_parse_result = parse_flag(args[i], valid, found, on_error);
		if (flag_parse_result == 1)
			return (i);
		else if (flag_parse_result == -1)
			return (-1);
		i++;
	}
	return (i);
}
