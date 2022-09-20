/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:14:26 by amann             #+#    #+#             */
/*   Updated: 2022/03/11 13:53:47 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
*	handling of flags is somewhat conversion-dependant.
*	# results in prefixing octal and hex conversions with 0 and 0x respectively
*	f conversions will always display a decimal point with this flag
*	0 pads all numeric conversions with '0' characters, but ignored if - flag
*	or precision value is given. Only works with width value
*	- left aligns output within field boundaries NB no effect without width
*	+ results in a sign ('+' or '-') always being printed before figure, negative
*	figures are signed by default. Only decimal conversions. Works with 0 flag
*	' ' leaves an empty space before positive numbers
*	% just prints a percentage sign.
*/

static int	zero_flag_check(t_flags flag)
{
	if (!flag.conv.b && flag.width.width && !flag.left)
	{
		if (!(flag.width.prec_set && flag.conv.numeric))
			return (TRUE);
	}
	return (FALSE);
}

static int	plus_flag_check(t_flags flag)
{
	if ((flag.conv.d || flag.conv.f) && !flag.conv.neg)
		return (TRUE);
	return (FALSE);
}

char	*flag_control(char *res, t_flags flag)
{
	int	len;

	if (!res || flag.conv.n)
		return (NULL);
	if (((flag.hash && flag.conv.numeric) && res[0] != '0') || flag.conv.p)
		res = handle_hash(res, flag);
	if (flag.zero && res)
	{
		if (zero_flag_check(flag))
			res = handle_zero(res, flag);
	}
	if ((flag.plus || flag.space) && res)
	{
		if (plus_flag_check(flag))
		{
			len = (int) ft_strlen(res);
			res = handle_plus(res, flag, len);
		}
	}
	return (res);
}
