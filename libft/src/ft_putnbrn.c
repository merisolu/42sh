/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:34:29 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/30 14:42:51 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Writes the given int to stdout, with the resulting output
 * being exactly the specified length. This means the number will either get
 * padding with zeros, print out completely, or be cut short.
*/
void	ft_putnbrn(int n, int len)
{
	ft_putnbrn_fd(n, len, 1);
}

/*
 * Writes the given long long to stdout, with the resulting output
 * being exactly the specified length. This means the number will either get
 * padding with zeros, print out completely, or be cut short.
*/
void	ft_putnbrn_llong(long long n, int len)
{
	ft_putnbrn_llong_fd(n, len, 1);
}

/*
 * Writes the given t_ull to stdout, with the resulting output
 * being exactly the specified length. This means the number will either get
 * padding with zeros, print out completely, or be cut short.
*/
void	ft_putnbrn_ullong(t_ull n, int len)
{
	ft_putnbrn_ullong_fd(n, len, 1);
}
