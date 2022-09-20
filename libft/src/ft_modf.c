/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:25:46 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/07 16:28:56 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_modf(double f, double *i)
{
	*i = (long long) f;
	return (f - *i);
}

long double	ft_modfl(long double f, long double *i)
{
	*i = (long long) f;
	return (f - *i);
}
