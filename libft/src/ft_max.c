/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:00:48 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/30 14:42:51 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns the larger one of the two given integers.*/
int	ft_max(int i1, int i2)
{
	if (i1 > i2)
		return (i1);
	return (i2);
}

/* Returns the larger one of the two given longs.*/
long	ft_max_long(long l1, long l2)
{
	if (l1 > l2)
		return (l1);
	return (l2);
}

/* Returns the larger one of the two given long longs.*/
long long	ft_max_llong(long long l1, long long l2)
{
	if (l1 > l2)
		return (l1);
	return (l2);
}

/* Returns the larger one of the two given t_ulls.*/
t_ull	ft_max_ullong(t_ull l1, t_ull l2)
{
	if (l1 > l2)
		return (l1);
	return (l2);
}

/* Returns the larger one of the two given size_t arguments.*/
size_t	ft_max_size_t(size_t s1, size_t s2)
{
	if (s1 > s2)
		return (s1);
	return (s2);
}
