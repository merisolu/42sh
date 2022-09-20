/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 13:31:56 by amann             #+#    #+#             */
/*   Updated: 2022/03/11 18:10:44 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 
*	if the precision is 0, simply chop off the decimal point and beyond
*	if we need a shorter number, we chop from the dp + precision
*	otherwise, pad out the number with 0s - remember to free memory!
*/

static char	*create_str_helper(char *int_str, char *dec_str, size_t signif)
{
	char	*zero_str;
	char	*temp_str;
	char	*res_str;

	zero_str = ft_strnew(signif);
	if (!zero_str)
		return (NULL);
	ft_memset((void *)zero_str, '0', signif);
	temp_str = ft_strjoin(".", zero_str);
	if (!temp_str)
		return (NULL);
	free(zero_str);
	zero_str = ft_strjoin(temp_str, dec_str);
	if (!zero_str)
		return (NULL);
	res_str = ft_strjoin(int_str, zero_str);
	if (!res_str)
		return (NULL);
	free(zero_str);
	free(temp_str);
	return (res_str);
}

static char	*create_string(long int l_dp, long double r_dp, size_t signif)
{
	char	*int_str;
	char	*dec_str;
	char	*res_str;
	char	*temp_str;

	int_str = ft_itoa_base(l_dp, BASE_TEN);
	if (!int_str)
		return (NULL);
	dec_str = ft_itoa_base((long int)r_dp, BASE_TEN);
	if (!dec_str)
		return (NULL);
	if (signif)
		res_str = create_str_helper(int_str, dec_str, signif);
	else
	{
		temp_str = ft_strjoin(".", dec_str);
		res_str = ft_strjoin(int_str, temp_str);
		if (temp_str)
			free(temp_str);
	}
	free(int_str);
	free(dec_str);
	return (res_str);
}

static size_t	check_sig_dig(long int l_dp, long double *r_dp, long double x)
{
	size_t		i;
	long double	temp;

	*r_dp = x - (long double)l_dp;
	temp = *r_dp;
	*r_dp *= 10e+17L;
	i = 0;
	while (temp < 1 && temp != ZERO_LONG_DOUBLE)
	{
		temp *= 10;
		i++;
	}
	if (i > 0)
		return (i - 1);
	else
		return (i);
}

static void	check_neg_double(long double *x, t_flags *flag)
{
	float	test;
	int		*ptr;

	if (*x == 0)
	{
		test = (float) *x;
		ptr = (int *) &test;
		if (((int) *ptr & 1 << 31) == 0)
			return ;
	}
	flag->conv.neg = TRUE;
	*x *= -1;
}

char	*convert_double(va_list lst, t_flags *flag)
{
	char		*res_str;
	long int	left_dp;
	long double	right_dp;
	long double	x;
	size_t		signif;

	set_x(lst, flag, &x);
	if (!flag->width.prec_set)
		flag->width.prec = 6;
	if (x <= 0)
		check_neg_double(&x, flag);
	left_dp = (long int) x;
	signif = check_sig_dig(left_dp, &right_dp, x);
	res_str = create_string(left_dp, right_dp, signif);
	if (flag->width.prec > 17)
		res_str = rounding_algo(res_str, 17);
	else
		res_str = rounding_algo(res_str, flag->width.prec);
	chop_chop(&res_str, flag->width.prec, flag->hash);
	res_str = neg_float_handler(res_str, flag);
	return (res_str);
}
