/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnumlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 10:22:23 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/30 14:42:51 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns how many characters are needed to store the given number. */
int	ft_getnumlen(int n)
{
	int	result;

	result = ft_getdigits(n);
	if (n < 0)
		result++;
	return (result);
}

/* Returns how many characters are needed to store the given number. */
int	ft_getnumlen_uint(unsigned int n)
{
	return (ft_getdigits_uint(n));
}

/* Returns how many characters are needed to store the given number. */
int	ft_getnumlen_llong(long long n)
{
	int	result;

	result = ft_getdigits_llong(n);
	if (n < 0)
		result++;
	return (result);
}

/* Returns how many characters are needed to store the given number. */
int	ft_getnumlen_ullong(t_ull n)
{
	return (ft_getdigits_ullong(n));
}
