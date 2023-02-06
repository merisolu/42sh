/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_test_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:49:59 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/06 14:58:45 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	cmd_test_numbers(char *op, char *arg_1, char *arg_2)
{
	long long	value_1;
	long long	value_2;

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
