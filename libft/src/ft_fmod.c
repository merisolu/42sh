/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 09:52:42 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/16 13:43:01 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_fmod(double f, double div)
{
	double	result;
	int		sign;

	if (div == 0.0)
		return (0);
	sign = ft_getsign_ldouble(f);
	result = f - (div * ft_round(f / div));
	if (sign)
		return (result);
	return (-result);
}

long double	ft_fmodl(long double f, long double div)
{
	long double	result;
	int			sign;

	if (div == 0.0L)
		return (0);
	sign = ft_getsign_ldouble(f);
	result = f - (div * (long long)(f / div));
	if (sign)
		return (result);
	return (-result);
}
