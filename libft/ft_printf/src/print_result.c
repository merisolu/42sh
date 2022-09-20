/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:37:43 by amann             #+#    #+#             */
/*   Updated: 2022/03/11 13:54:24 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*print_result_helper(char *new, t_flags flag)
{
	free(new);
	if (flag.conv.p)
		return (ft_strdup("0x"));
	else
	{
		return (ft_strdup(""));
	}
}

static int	nil_check_1(t_flags flag)
{
	if (flag.conv.numeric && flag.nil && !flag.width.prec)
	{
		if (flag.width.prec_set && flag.width.width && !flag.plus)
			return (TRUE);
	}
	return (FALSE);
}

static int	nil_check_2(t_flags flag)
{
	if (flag.conv.numeric && flag.nil && !flag.width.prec)
	{
		if (flag.width.prec_set && !(flag.conv.o && flag.hash))
		{
			if (!flag.plus && !(flag.conv.d && !flag.width.width))
				return (TRUE);
		}
	}		
	return (FALSE);
}

void	print_result(char *res, t_flags flag, int *printf_ret)
{
	char	*new;
	t_width	w;

	w = flag.width;
	if (!res || flag.conv.n)
		return ;
	new = set_memory(res, w, flag);
	if (!new)
		return ;
	if (flag.conv.numeric)
		precision_helper(res, new, w, flag);
	if (nil_check_1(flag))
		ft_memset(new, ' ', ft_strlen(new));
	else if (nil_check_2(flag))
		new = print_result_helper(new, flag);
	if (!new)
		return ;
	ft_printf_putstr(new, printf_ret, flag);
	free(new);
}
