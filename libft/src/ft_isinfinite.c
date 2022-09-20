/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinfinite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:16:43 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/16 14:23:41 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns the sign of the infinity if the number is infinite, zero otherwise.
 */
int	ft_isinfinite(double n)
{
	union u_double_bytes	data;

	data.number = n;
	if ((data.bytes[7] & 127) == 127 && (data.bytes[6] & 240) == 240
		&& ft_abs_double(ft_getmantissa(n)) == 0.5)
		return (ft_getsign_double(n));
	return (0);
}

/*
 * Returns the sign of the infinity if the number is infinite, zero otherwise.
 * Assumes x86 extended precision format (80-bits)!
 */
int	ft_isinfinite_long(long double n)
{
	union u_ldouble_bytes	data;

	data.number = n;
	if ((data.bytes[9] & 127) == 127 && (data.bytes[8] & 255) == 255
		&& ft_abs_ldouble(ft_getmantissa_long(n)) == 0.5)
		return (ft_getsign_ldouble(n));
	return (0);
}
