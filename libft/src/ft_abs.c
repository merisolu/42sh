/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:02:40 by jumanner          #+#    #+#             */
/*   Updated: 2022/01/24 13:04:35 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Returns the absolute value of i. */
int	ft_abs(int i)
{
	if (i >= 0)
		return (i);
	return (-i);
}

/* Returns the absolute value of i. */
long	ft_abs_long(long i)
{
	if (i >= 0)
		return (i);
	return (-i);
}

/* Returns the absolute value of i. */
long long	ft_abs_llong(long long i)
{
	if (i >= 0)
		return (i);
	return (-i);
}
