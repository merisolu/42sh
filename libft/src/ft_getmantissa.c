/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getmantissa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:16:43 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/11 23:38:16 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Gets the mantissa of the given double by setting the exponent to the bias. */
double	ft_getmantissa(double n)
{
	union u_double_bytes	data;

	data.number = n;
	data.bytes[7] &= 128;
	data.bytes[7] |= 63;
	data.bytes[6] &= 15;
	data.bytes[6] |= 224;
	return (data.number);
}

/* 
 * Gets the mantissa of the given value by setting the exponent to the bias.
 * Assumes x86 extended precision format (80-bits)!
 */
long double	ft_getmantissa_long(long double n)
{
	union u_ldouble_bytes	data;

	data.number = n;
	data.bytes[9] &= 128;
	data.bytes[9] |= 63;
	data.bytes[8] = 254;
	return (data.number);
}
