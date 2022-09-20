/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:42:19 by amann             #+#    #+#             */
/*   Updated: 2022/09/20 16:37:45 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printf_loop(int fd, const char *s, va_list lst, int *ret)
{
	size_t	count;
	t_loop	l;

	count = 0;
	l.i = 0;
	l.fd = fd;
	while (s[l.i] != '\0')
	{
		if (s[l.i] == '%' || s[l.i] == '{')
		{
			ft_printf_putchar(fd, s + count, l.i - count, ret);
			if (s[l.i + 1] == '\0' && s[l.i] == '%')
				return ;
			if (s[l.i] == '{')
				check_colour(fd, s + l.i, &(l.i), ret);
			else
				ft_printf_ctrl((s + l.i + 1), lst, &l, ret);
			count = l.i + 1;
		}
		(l.i)++;
	}
	ft_printf_putchar(fd, s + count, l.i - count, ret);
}

int	ft_printf(const char *s, ...)
{
	va_list	lst;
	int		ret;

	va_start(lst, s);
	ret = 0;
	ft_printf_loop(STDOUT_FILENO, s, lst, &ret);
	va_end(lst);
	return (ret);
}

int	ft_dprintf(int fd, const char *s, ...)
{
	va_list	lst;
	int		ret;

	if (fd < 0)
		return (0);
	va_start(lst, s);
	ret = 0;
	ft_printf_loop(fd, s, lst, &ret);
	va_end(lst);
	return (ret);
}
