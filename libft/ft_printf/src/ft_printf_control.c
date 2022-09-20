/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:22:16 by amann             #+#    #+#             */
/*   Updated: 2022/03/11 13:54:32 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	conv_char(char c)
{
	char	*test;

	if (!ft_isalpha(c))
		return (FALSE);
	test = ft_strchr(CONV_CHARS, c);
	if (test)
		return (TRUE);
	else
		return (FALSE);
}

static int	lm_char(char c)
{
	if (c == 'h' || c == 'l' || c == 'L' || c == 'z')
		return (TRUE);
	return (FALSE);
}

static size_t	control_loop(const char *s, va_list lst, t_flags *flag_data)
{
	int	i;

	i = 0;
	while ((!conv_char(s[i]) && s[i] != '%' && s[i] != '\0') || lm_char(s[i]))
	{
		if ((ft_isalpha(s[i]) && !lm_char(s[i])))
			break ;
		if ((ft_isdigit(s[i]) && s[i] != '0') || s[i] == '.' || s[i] == '*')
			set_width_prec(s + i, flag_data, &i, lst);
		set_flags_and_length(s + i, flag_data, &i);
		i++;
	}
	return ((size_t)i);
}

void	ft_printf_ctrl(const char *s, va_list lst, size_t *p_i, int *p_ret)
{
	size_t	i;
	t_flags	flag_data;
	char	*res;

	initialise_structs(&flag_data);
	res = NULL;
	i = control_loop(s, lst, &flag_data);
	if (s[i] == '\0' || (ft_isalpha(s[i]) && !conv_char(s[i])))
	{
		*p_i += i;
		return ;
	}
	res = conversion_ctrl(s + i, lst, &flag_data, p_ret);
	res = flag_control(res, flag_data);
	print_result(res, flag_data, p_ret);
	if (res)
		free(res);
	*p_i += i + 1;
}
