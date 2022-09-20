/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:36:04 by jumanner          #+#    #+#             */
/*   Updated: 2022/08/31 10:08:26 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Writes the given int to the given file descriptor. */
void	ft_putnbr_fd(int n, int fd)
{
	if (n == INT_MIN)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	if (n >= 0)
		ft_putchar_fd((n % 10) + 48, fd);
}

/* Writes the given long long to the given file descriptor. */
void	ft_putnbr_llong_fd(long long n, int fd)
{
	if (n == (long long) LLONG_MIN)
	{
		ft_putstr_fd("-9223372036854775808", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n > 9)
		ft_putnbr_llong_fd(n / 10, fd);
	if (n >= 0)
		ft_putchar_fd((n % 10) + 48, fd);
}

/* Writes the given t_ull to the given file descriptor. */
void	ft_putnbr_ullong_fd(t_ull n, int fd)
{
	if (n > 9)
		ft_putnbr_ullong_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + 48, fd);
}
