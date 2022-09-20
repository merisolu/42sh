/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:12:50 by amann             #+#    #+#             */
/*   Updated: 2022/09/20 15:34:40 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_putchar(int fd, char const *str, size_t i, int *printf_res)
{
	ssize_t		count;

	count = write(fd, str, i);
	*printf_res += (int) count;
}

void	ft_printf_putstr(int fd, char const *str, int *printf_res, t_flags flag)
{
	size_t	i;
	char	*temp;

	if (!str)
		return ;
	i = 0;
	while (str[i] != '\0')
		i++;
	if (flag.conv.c && flag.nil)
	{
		temp = ft_strchr(str, '0');
		*temp = '\0';
	}
	ft_printf_putchar(fd, str, i, printf_res);
}
