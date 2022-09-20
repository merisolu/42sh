/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:26:46 by amann             #+#    #+#             */
/*   Updated: 2022/03/11 14:02:28 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*convert_us_helper(va_list lst, t_flags *flag, int base)
{
	if (flag->ll && !flag->z)
		return (handle_ull(va_arg(lst, unsigned long long), flag, base));
	else if ((flag->l || flag->conv.p) && !flag->z)
		return (handle_ul(va_arg(lst, unsigned long), flag, base));
	else if (flag->h && !flag->z)
		return (handle_uh(va_arg(lst, unsigned int), flag, base));
	else if (flag->hh && !flag->z)
		return (handle_uhh(va_arg(lst, unsigned int), flag, base));
	else if (flag->z && flag->conv.u)
		return (handle_zu(va_arg(lst, size_t), flag, base));
	else
		return (handle_uint(va_arg(lst, unsigned int), flag, base));
}

char	*convert_unsigned(va_list lst, t_flags *flag)
{
	size_t				i;
	char				*res;

	if (flag->conv.u)
		return (convert_us_helper(lst, flag, BASE_TEN));
	else if (flag->conv.o)
		return (convert_us_helper(lst, flag, BASE_EIGHT));
	else if (flag->conv.big_x)
		return (convert_us_helper(lst, flag, BASE_SIXTEEN));
	else if (flag->conv.b)
		return (convert_us_helper(lst, flag, BASE_TWO));
	else
	{
		res = convert_us_helper(lst, flag, BASE_SIXTEEN);
		i = 0;
		while (res[i] != '\0')
		{
			res[i] = ft_tolower(res[i]);
			i++;
		}
		return (res);
	}
}

char	*convert_digit(va_list lst, t_flags *flag)
{
	if (flag->ll && !flag->z)
		return (handle_ll(va_arg(lst, long long), flag));
	else if (flag->l && !flag->z)
		return (handle_l(va_arg(lst, long), flag));
	else if (flag->h && !flag->z)
		return (handle_h(va_arg(lst, int), flag));
	else if (flag->hh && !flag->z)
		return (handle_hh(va_arg(lst, int), flag));
	else if (flag->z && flag->conv.d)
		return (handle_zd(va_arg(lst, ssize_t), flag));
	else
		return (handle_int(va_arg(lst, int), flag));
}
