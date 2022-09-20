/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:19:39 by jumanner          #+#    #+#             */
/*   Updated: 2022/08/26 14:46:03 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_result(unsigned long result, int sign)
{
	if (result > 9223372036854775807)
	{
		if (sign == -1)
			return (0);
		else if (result != 9223372036854775807)
			return (-1);
	}
	return (result * sign);
}

/* Turns the given string str into the integer it represents if possible.
 * Returns the result. */
int	ft_atoi(const char *str)
{
	unsigned long	result;
	int				sign;

	sign = 1;
	result = 0;
	while (*str && *str != '-' && *str != '+' && ft_is_whitespace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (ft_isdigit(*str))
			result = (result * 10) + *str - '0';
		else
			break ;
		str++;
	}
	return (get_result(result, sign));
}
