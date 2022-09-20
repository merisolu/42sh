/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 09:15:18 by jumanner          #+#    #+#             */
/*   Updated: 2022/01/27 09:19:13 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Returns the absolute value of f. */
double	ft_abs_double(double f)
{
	if (f >= 0)
		return (f);
	return (-f);
}

/* Returns the absolute value of f. */
long double	ft_abs_ldouble(long double f)
{
	if (f >= 0)
		return (f);
	return (-f);
}
