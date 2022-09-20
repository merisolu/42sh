/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed_conversion_handlers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:39:08 by amann             #+#    #+#             */
/*   Updated: 2022/03/04 11:25:10 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_ll(long long ll_x, t_flags *flag)
{
	char	*res;
	int		min_flag;

	min_flag = FALSE;
	if (ll_x < 0)
		flag->conv.neg = TRUE;
	if (ll_x == 0)
		flag->nil = TRUE;
	if (ll_x == LLONG_MIN)
	{
		min_flag = TRUE;
		ll_x += 1;
	}
	res = ft_itoa_base(ft_abs_long(ll_x), BASE_TEN);
	if (flag->conv.neg)
		res = add_sign(res);
	if (min_flag)
		res[ft_strlen(res) - 1] = '8';
	return (res);
}

char	*handle_l(long l_x, t_flags *flag)
{
	char	*res;
	int		min_flag;

	min_flag = FALSE;
	if (l_x < 0)
		flag->conv.neg = TRUE;
	if (l_x == 0)
		flag->nil = TRUE;
	if (l_x == LONG_MIN)
	{
		min_flag = TRUE;
		l_x += 1;
	}
	res = ft_itoa_base(ft_abs_long(l_x), BASE_TEN);
	if (flag->conv.neg)
		res = add_sign(res);
	if (min_flag)
		res[ft_strlen(res) - 1] = '8';
	return (res);
}

char	*handle_h(int x, t_flags *flag)
{
	char	*res;
	short	h_x;

	h_x = (short) x;
	if (h_x < 0)
		flag->conv.neg = TRUE;
	if (h_x == 0)
		flag->nil = TRUE;
	res = ft_itoa_base((long long) ft_abs((int)h_x), BASE_TEN);
	if (flag->conv.neg)
		res = add_sign(res);
	return (res);
}

char	*handle_hh(int x, t_flags *flag)
{
	char	*res;
	char	hh_x;

	hh_x = (char) x;
	if (hh_x < 0)
		flag->conv.neg = TRUE;
	if (hh_x == 0)
		flag->nil = TRUE;
	res = ft_itoa_base((long long) ft_abs((int)hh_x), BASE_TEN);
	if (flag->conv.neg)
		res = add_sign(res);
	return (res);
}

char	*handle_int(int x, t_flags *flag)
{
	char	*res;
	int		min_flag;

	min_flag = FALSE;
	if (x < 0)
		flag->conv.neg = TRUE;
	if (x == 0)
		flag->nil = TRUE;
	if (x == INT_MIN)
	{
		min_flag = TRUE;
		x += 1;
	}
	res = ft_itoa_base((long long) ft_abs(x), BASE_TEN);
	if (flag->conv.neg)
		res = add_sign(res);
	if (min_flag)
		res[ft_strlen(res) - 1] = '8';
	return (res);
}
