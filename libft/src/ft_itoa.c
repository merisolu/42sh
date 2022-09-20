/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:56:48 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/30 14:42:51 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Turns the given integer n into a string representation. */
char	*ft_itoa(int n)
{
	return (ft_itoa_base(n, 10));
}

/* Turns the given unsigned integer n into a string representation. */
char	*ft_itoa_uint(unsigned int n)
{
	return (ft_itoa_uint_base(n, 10));
}

/* Turns the given long long n into a string representation. */
char	*ft_itoa_llong(long long n)
{
	return (ft_itoa_llong_base(n, 10));
}

/* Turns the given t_ull n into a string representation. */
char	*ft_itoa_ullong(t_ull n)
{
	return (ft_itoa_ullong_base(n, 10));
}
