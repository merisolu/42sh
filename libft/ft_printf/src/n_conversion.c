/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_conversion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:31:57 by amann             #+#    #+#             */
/*   Updated: 2022/03/04 13:32:33 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	convert_n(va_list lst, t_flags *flag, int *p_ret)
{
	if (flag->ll)
		*(va_arg(lst, long long *)) = (long long) *p_ret;
	else if (flag->l)
		*(va_arg(lst, long *)) = (long) *p_ret;
	else if (flag->h)
		*(va_arg(lst, short *)) = (short) *p_ret;
	else if (flag->hh)
		*(va_arg(lst, char *)) = (char) *p_ret;
	else
		*(va_arg(lst, int *)) = *p_ret;
}
