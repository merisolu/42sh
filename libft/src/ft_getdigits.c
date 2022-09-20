/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getdigits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 10:22:23 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/30 14:51:14 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns the number of digits in an integer. */
int	ft_getdigits(int n)
{
	int	result;

	if (n == 0)
		return (1);
	result = 0;
	while (n)
	{
		n /= 10;
		result++;
	}
	return (result);
}

/* Returns the number of digits in an unsigned int. */
int	ft_getdigits_uint(unsigned int n)
{
	int	result;

	if (n == 0)
		return (1);
	result = 0;
	while (n)
	{
		n /= 10;
		result++;
	}
	return (result);
}

/* Returns the number of digits in long long. */
int	ft_getdigits_llong(long long n)
{
	int	result;

	if (n == 0)
		return (1);
	result = 0;
	while (n)
	{
		n /= 10;
		result++;
	}
	return (result);
}

/* Returns the number of digits in an t_ull. */
int	ft_getdigits_ullong(t_ull n)
{
	int	result;

	if (n == 0)
		return (1);
	result = 0;
	while (n)
	{
		n /= 10;
		result++;
	}
	return (result);
}
