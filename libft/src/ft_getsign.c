/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getsign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:16:43 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/11 23:36:20 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Gets the sign of the number. Returns 1 for zero. */
int	ft_getsign(int n)
{
	if (n < 0)
		return (-1);
	return (1);
}

/* Gets the sign of the number. Returns 1 for zero. */
int	ft_getsign_llong(long long n)
{
	if (n < 0)
		return (-1);
	return (1);
}

/* Gets the sign of the number. Returns 1 for zero. */
int	ft_getsign_double(double n)
{
	union u_double_bytes	data;

	data.number = n;
	if (data.bytes[7] & 128)
		return (-1);
	return (1);
}

/* Gets the sign of the number. Returns 1 for zero. */
int	ft_getsign_ldouble(long double n)
{
	union u_ldouble_bytes	data;

	data.number = n;
	if (data.bytes[9] & 128)
		return (-1);
	return (1);
}
