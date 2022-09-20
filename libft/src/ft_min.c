/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:02:13 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/30 14:42:51 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns the smaller one of the two given integers.*/
int	ft_min(int i1, int i2)
{
	if (i1 < i2)
		return (i1);
	return (i2);
}

/* Returns the smaller one of the two given longs.*/
long	ft_min_long(long i1, long i2)
{
	if (i1 < i2)
		return (i1);
	return (i2);
}

/* Returns the smaller one of the two given long longs.*/
long long	ft_min_llong(long long i1, long long i2)
{
	if (i1 < i2)
		return (i1);
	return (i2);
}

/* Returns the smaller one of the two given t_ulls.*/
t_ull	ft_min_ullong(t_ull i1, t_ull i2)
{
	if (i1 < i2)
		return (i1);
	return (i2);
}

/* Returns the smaller one of the two given size_t arguments.*/
size_t	ft_min_size_t(size_t i1, size_t i2)
{
	if (i1 < i2)
		return (i1);
	return (i2);
}
