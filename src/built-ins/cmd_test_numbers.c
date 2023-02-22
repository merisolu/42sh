/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_test_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:49:59 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/22 14:44:06 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static int	check_for_invalid_arguments(char *arg_1, char *arg_2)
{
	char	*invalid_argument;

	invalid_argument = NULL;
	if (!ft_isdigit_str(arg_2)
		&& !(ft_strchr("-+", arg_2[0]) && ft_isdigit_str(arg_2 + 1)))
		invalid_argument = arg_2;
	if (!ft_isdigit_str(arg_1)
		&& !(ft_strchr("-+", arg_1[0]) && ft_isdigit_str(arg_1 + 1)))
		invalid_argument = arg_1;
	if (invalid_argument)
		return (print_error_bool(true, ERRTEMPLATE_DOUBLE_NAMED,
				"test", invalid_argument, "integer expression expected"));
	return (false);
}

int	cmd_test_numbers(char *op, char *arg_1, char *arg_2)
{
	long long	value_1;
	long long	value_2;

	if (check_for_invalid_arguments(arg_1, arg_2))
		return (2);
	value_1 = ft_atoll(arg_1);
	value_2 = ft_atoll(arg_2);
	if (ft_strequ(op, "-eq"))
		return (!(value_1 == value_2));
	if (ft_strequ(op, "-ne"))
		return (!(value_1 != value_2));
	if (ft_strequ(op, "-gt"))
		return (!(value_1 > value_2));
	if (ft_strequ(op, "-ge"))
		return (!(value_1 >= value_2));
	if (ft_strequ(op, "-lt"))
		return (!(value_1 < value_2));
	if (ft_strequ(op, "-le"))
		return (!(value_1 <= value_2));
	return (1);
}
