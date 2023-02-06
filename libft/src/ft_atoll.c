/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:59:05 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/06 14:59:39 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Turns the given string into a long long.
 */
long long	ft_atoll(const char *str)
{
	long long	result;
	long long	temp;
	long long	sign;

	sign = 1;
	result = 0;
	while (ft_is_whitespace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		temp = (result * 10) + (*str - '0');
		if (temp < result)
			return (-1);
		result = temp;
		str++;
	}
	return (result * sign);
}
