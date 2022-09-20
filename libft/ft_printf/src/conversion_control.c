/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:16:46 by amann             #+#    #+#             */
/*   Updated: 2022/01/20 10:16:46 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*handle_percent(void)
{
	char	*res;

	res = ft_strnew(1);
	if (!res)
		return (NULL);
	res[0] = '%';
	return (res);
}

static char	*convert_char(va_list lst, t_flags *flag)
{
	char			*res;
	unsigned char	c;

	c = (unsigned char) va_arg(lst, int);
	res = ft_strnew(1);
	if (!res)
		return (NULL);
	if (!c)
	{
		flag->nil = TRUE;
		res[0] = '0';
		return (res);
	}
	res[0] = c;
	return (res);
}

static char	*convert_string(va_list lst, t_flags *flag)
{
	char	*res;
	char	*temp;

	res = ft_strdup(va_arg(lst, char *));
	if (!res)
	{
		res = ft_strdup("(null)");
		if (!res)
			return (NULL);
	}
	if (flag->width.prec_set)
	{
		temp = ft_strnew(flag->width.prec);
		if (!temp)
			return (NULL);
		ft_strncpy(temp, res, flag->width.prec);
		free(res);
		res = temp;
	}
	return (res);
}

static char	*conversion_dispatcher(char *(*p[5])(va_list lst, t_flags *flag),	\
		va_list lst, t_flags *flag, int *p_ret)
{
	if (flag->conv.d)
		return ((*p[0])(lst, flag));
	else if (flag->conv.u || flag->conv.o || flag->conv.x || flag->conv.big_x \
		|| flag->conv.p || flag->conv.b)
		return ((*p[1])(lst, flag));
	else if (flag->conv.c)
		return ((*p[2])(lst, flag));
	else if (flag->conv.s)
		return ((*p[3])(lst, flag));
	else if (flag->conv.f)
		return ((*p[4])(lst, flag));
	else if (flag->conv.percent)
		return (handle_percent());
	else if (flag->conv.n)
		convert_n(lst, flag, p_ret);
	return (NULL);
}

char	*conversion_ctrl(const char *s, va_list lst, t_flags *flag, int *p_ret)
{
	char	*(*p[5])(va_list lst, t_flags *flag);
	char	*res;

	p[0] = convert_digit;
	p[1] = convert_unsigned;
	p[2] = convert_char;
	p[3] = convert_string;
	p[4] = convert_double;
	res = NULL;
	set_conv_type(s[0], &(flag->conv));
	res = conversion_dispatcher(p, lst, flag, p_ret);
	if (flag->conv.numeric && flag->nil && !flag->width.prec
		&& flag->width.prec_set)
	{
		free(res);
		res = ft_strdup("");
		if (!res)
			return (NULL);
	}
	return (res);
}
