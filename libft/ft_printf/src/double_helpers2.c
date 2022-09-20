/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:56:11 by amann             #+#    #+#             */
/*   Updated: 2022/02/21 17:57:20 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_x(va_list lst, t_flags *flag, long double *x)
{
	if (flag->big_l)
		*x = va_arg(lst, long double);
	else
		*x = (long double)va_arg(lst, double);
}
