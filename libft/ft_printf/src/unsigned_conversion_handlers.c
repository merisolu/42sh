/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_conversion_handlers.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:01:30 by amann             #+#    #+#             */
/*   Updated: 2022/09/20 14:44:50 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_ull(unsigned long long ll_x, t_flags *flag, int base)
{
	if (ll_x == 0)
		flag->nil = TRUE;
	return (ft_itoa_ullong_base(ll_x, base));
}

char	*handle_ul(unsigned long l_x, t_flags *flag, int base)
{
	if (l_x == 0)
		flag->nil = TRUE;
	return (ft_itoa_ullong_base((unsigned long long)l_x, base));
}

char	*handle_uh(unsigned int x, t_flags *flag, int base)
{
	unsigned short	h_x;

	h_x = (unsigned short) x;
	if (h_x == 0)
		flag->nil = TRUE;
	return (ft_itoa_ullong_base((unsigned long long)h_x, base));
}

char	*handle_uhh(unsigned int x, t_flags *flag, int base)
{
	unsigned char	hh_x;

	hh_x = (unsigned char) x;
	if (hh_x == 0)
		flag->nil = TRUE;
	return (ft_itoa_ullong_base((unsigned long long)hh_x, base));
}

char	*handle_uint(unsigned int x, t_flags *flag, int base)
{
	if (x == 0)
		flag->nil = TRUE;
	return (ft_itoa_ullong_base((unsigned long long)x, base));
}
