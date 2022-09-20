/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frexp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:55:48 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/11 23:38:36 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns the mantissa of the value, and sets the exponent to the int pointed
 * to by *exp, so that the end result is value = mantissa * 2^exponent
*/
double	ft_frexp(double value, int *exp)
{
	*exp = ft_getexponent(value);
	return (ft_getmantissa(value));
}

/*
 * Returns the mantissa of the value, and sets the exponent to the int pointed
 * to by *exp, so that the end result is value = mantissa * 2^exponent
*/
long double	ft_frexpl(long double value, int *exp)
{
	*exp = ft_getexponent_long(value);
	return (ft_getmantissa_long(value));
}
