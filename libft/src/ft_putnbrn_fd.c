/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrn_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:36:04 by jumanner          #+#    #+#             */
/*   Updated: 2022/08/26 14:53:06 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Writes the given int to the given file descriptor, with the resulting output
 * being exactly the specified length. This means the number will either get
 * padding with zeros, print out completely, or be cut short.
*/
void	ft_putnbrn_fd(int n, int len, int fd)
{
	if (len <= 0)
		return ;
	if (n == INT_MIN)
	{
		ft_putchar_fd('-', fd);
		ft_putcharn_fd('0', len - 11, fd);
		ft_putstrn_fd("2147483648", len - 1, fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		len--;
		n *= -1;
	}
	if (ft_getnumlen(n) < len)
	{
		ft_putchar_fd('0', fd);
		ft_putnbrn_fd(n, len - 1, fd);
		return ;
	}
	if (len && n > 9)
		ft_putnbrn_fd(n / 10, len - 1, fd);
	if (len && n >= 0)
		ft_putchar_fd((n % 10) + 48, fd);
}

/*
 * Writes the given long long to the given file descriptor, with the resulting
 * output being exactly the specified length. This means the number will either
 * get padding with zeros, print out completely, or be cut short.
*/
void	ft_putnbrn_llong_fd(long long n, int len, int fd)
{
	if (len <= 0)
		return ;
	if (n == (long long) LLONG_MIN)
	{
		ft_putchar_fd('-', fd);
		ft_putcharn_fd('0', len - 20, fd);
		ft_putstrn_fd("9223372036854775808", len - 1, fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		len--;
		n *= -1;
	}
	if (ft_getnumlen_llong(n) < len)
	{
		ft_putchar_fd('0', fd);
		ft_putnbrn_llong_fd(n, len - 1, fd);
		return ;
	}
	if (len && n > 9)
		ft_putnbrn_llong_fd(n / 10, len - 1, fd);
	if (len && n >= 0)
		ft_putchar_fd((n % 10) + 48, fd);
}

/*
 * Writes the given t_ull to the given file descriptor, with the
 * resulting output being exactly the specified length. This means the number
 * will either get padding with zeros, print out completely, or be cut short.
*/
void	ft_putnbrn_ullong_fd(t_ull n, int len, int fd)
{
	if (len <= 0)
		return ;
	if (ft_getnumlen_ullong(n) < len)
	{
		ft_putchar_fd('0', fd);
		ft_putnbrn_ullong_fd(n, len - 1, fd);
		return ;
	}
	if (n > 9)
		ft_putnbrn_ullong_fd(n / 10, len - 1, fd);
	ft_putchar_fd((n % 10) + 48, fd);
}
