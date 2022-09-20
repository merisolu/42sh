/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:12:21 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/09 15:12:25 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_pow(int n, unsigned int pow)
{
	if (pow == 0)
		return (1);
	return (n * ft_pow(n, pow - 1));
}

long	ft_pow_long(long n, unsigned int pow)
{
	if (pow == 0)
		return (1);
	return (n * ft_pow(n, pow - 1));
}

long long	ft_pow_llong(long long n, unsigned int pow)
{
	if (pow == 0)
		return (1);
	return (n * ft_pow(n, pow - 1));
}

double	ft_pow_double(double n, int pow)
{
	if (pow == 0)
		return (1);
	if (pow < 0)
		return (1.0 / ft_pow_double(n, -pow));
	return (n * ft_pow_double(n, pow - 1));
}

long double	ft_pow_ldouble(long double n, int pow)
{
	if (pow == 0)
		return (1);
	if (pow < 0)
		return (1.0 / ft_pow_ldouble(n, -pow));
	return (n * ft_pow_ldouble(n, pow - 1));
}
