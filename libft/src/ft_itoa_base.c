/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:56:48 by jumanner          #+#    #+#             */
/*   Updated: 2022/09/12 14:04:27 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Turns the given integer n into a string representation in bases 2 to 36. */
char	*ft_itoa_base(int n, int base)
{
	char	*result;
	int		size;
	char	*chars;

	if (base < 2 || base > 36)
		return (NULL);
	if (base != 10 && n < 0)
		return (ft_itoa_uint_base((unsigned int) n, base));
	chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	size = ft_getdigits_base(n, base) + (n < 0);
	result = ft_strnew(size);
	if (!result)
		return (NULL);
	if (n < 0)
		result[0] = '-';
	else if (n == 0)
		result[0] = '0';
	while (n)
	{
		result[(size--) - 1] = chars[ft_abs(n % base)];
		n = n / base;
	}
	return (result);
}

/* 
 * Turns the given unsigned integer n into a string representation 
 * in bases 2 to 36.
*/
char	*ft_itoa_uint_base(unsigned int n, unsigned int base)
{
	char	*result;
	int		size;
	char	*chars;

	if (base < 2 || base > 36)
		return (NULL);
	chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	size = ft_getdigits_uint_base(n, base);
	result = ft_strnew(size);
	if (!result)
		return (NULL);
	if (n == 0)
		result[0] = '0';
	while (n)
	{
		result[(size--) - 1] = chars[n % base];
		n = n / base;
	}
	return (result);
}

/* Turns the given long long n into a string representation in bases 2 to 36. */
char	*ft_itoa_llong_base(long long n, int base)
{
	char	*result;
	int		size;
	char	*chars;

	if (base < 2 || base > 36)
		return (NULL);
	if (base != 10 && n < 0)
		return (ft_itoa_ullong_base((t_ull) n, base));
	chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	size = ft_getdigits_llong_base(n, base) + (n < 0);
	result = ft_strnew(size);
	if (!result)
		return (NULL);
	if (n < 0)
		result[0] = '-';
	else if (n == 0)
		result[0] = '0';
	while (n)
	{
		result[(size--) - 1] = chars[ft_abs(n % base)];
		n = n / base;
	}
	return (result);
}

/* 
 * Turns the given t_ull n into a string representation
 * in bases 2 to 36.
*/
char	*ft_itoa_ullong_base(t_ull n, int base)
{
	char	*result;
	int		size;
	char	*chars;

	if (base < 2 || base > 36)
		return (NULL);
	chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	size = ft_getdigits_ullong_base(n, base);
	result = ft_strnew(size);
	if (!result)
		return (NULL);
	if (n == 0)
		result[0] = '0';
	while (n)
	{
		result[(size--) - 1] = chars[n % base];
		n /= base;
	}
	return (result);
}
