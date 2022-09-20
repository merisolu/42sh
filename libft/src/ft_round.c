/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:01:41 by jumanner          #+#    #+#             */
/*   Updated: 2022/01/31 17:01:58 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_round(double f)
{
	long long	i;
	long long	sign;

	sign = 1;
	if (f < 0)
		sign = -1;
	f = ft_abs_ldouble(f);
	i = (long long) f;
	if (i == 0 && f >= 0.5)
		return (1 * sign);
	f = ft_fmodl(f, i);
	if (f >= 0.5)
		return ((i + 1) * sign);
	return (i * sign);
}

long long	ft_round_long(long double f)
{
	long long	i;
	long long	sign;

	sign = 1;
	if (f < 0)
		sign = -1;
	f = ft_abs_ldouble(f);
	i = (long long) f;
	if (i == 0 && f >= 0.5)
		return (1 * sign);
	f = ft_fmodl(f, i);
	if (f >= 0.5)
		return ((i + 1) * sign);
	return (i * sign);
}
