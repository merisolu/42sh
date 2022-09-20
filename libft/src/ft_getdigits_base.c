/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getdigits_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 10:22:23 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/30 14:42:51 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns the number of digits in an integer. */
int	ft_getdigits_base(int c, int base)
{
	int	result;

	c = ft_abs(c);
	result = 0;
	if (c == 0)
		return (1);
	while (c)
	{
		c /= base;
		result++;
	}
	return (result);
}

/* Returns the number of digits in an unsigned integer. */
int	ft_getdigits_uint_base(unsigned int c, int base)
{
	int	result;

	result = 0;
	if (c == 0)
		return (1);
	while (c)
	{
		c /= base;
		result++;
	}
	return (result);
}

/* Returns the number of digits in a long long. */
int	ft_getdigits_llong_base(long long c, int base)
{
	int	result;

	c = ft_abs_llong(c);
	result = 0;
	if (c == 0)
		return (1);
	while (c)
	{
		c /= base;
		result++;
	}
	return (result);
}

/* Returns the number of digits in an t_ull. */
int	ft_getdigits_ullong_base(t_ull c, int base)
{
	int	result;

	result = 0;
	if (c == 0)
		return (1);
	while (c)
	{
		c /= base;
		result++;
	}
	return (result);
}
