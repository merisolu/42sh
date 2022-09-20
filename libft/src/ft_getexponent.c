/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getexponent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:16:43 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/11 22:48:28 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Gets the exponent of the given double. */
int	ft_getexponent(double n)
{
	union u_double_bytes	data;
	short					result;
	short					second_byte;

	data.number = n;
	result = data.bytes[8 - 1];
	second_byte = data.bytes[8 - 2];
	result = result << 4;
	second_byte = second_byte >> 4;
	result |= second_byte;
	result -= 1022;
	return (result);
}

/*
 * Gets the exponent of the given long double.
 * Assumes x86 extended precision format (80-bits)!
 */
int	ft_getexponent_long(long double n)
{
	union u_ldouble_bytes	data;
	short					result;

	data.number = n;
	result = 0;
	result |= data.bytes[9];
	result = result << 8;
	result |= data.bytes[8];
	result &= 32767;
	return (result - 16382);
}
