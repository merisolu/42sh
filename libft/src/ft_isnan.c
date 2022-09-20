/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:16:43 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/16 14:23:43 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns true if the given double is NaN.
 */
int	ft_isnan(double n)
{
	union u_double_bytes	data;

	if (ft_getsign_double(n) == -1)
		return (0);
	data.number = n;
	if ((data.bytes[7] & 127) == 127
		&& (data.bytes[6] & 248) == 248
		&& data.bytes[5] == 0
		&& data.bytes[4] == 0
		&& data.bytes[3] == 0
		&& data.bytes[2] == 0
		&& data.bytes[1] == 0
		&& data.bytes[0] == 0)
		return (1);
	return (0);
}

/*
 * Returns true if the given long double is NaN.
 * Assumes x86 extended precision format (80-bits)!
 */
int	ft_isnan_long(long double n)
{
	union u_ldouble_bytes	data;

	if (ft_getsign_ldouble(n) == -1)
		return (0);
	data.number = n;
	if ((data.bytes[9] & 127) == 127
		&& (data.bytes[8] & 255) == 255
		&& (data.bytes[7] & 192) == 192
		&& data.bytes[6] == 0
		&& data.bytes[5] == 0
		&& data.bytes[4] == 0
		&& data.bytes[3] == 0
		&& data.bytes[2] == 0
		&& data.bytes[1] == 0
		&& data.bytes[0] == 0
	)
		return (1);
	return (0);
}
