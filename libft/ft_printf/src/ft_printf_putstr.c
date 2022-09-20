/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:12:50 by amann             #+#    #+#             */
/*   Updated: 2022/03/16 13:56:52 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_putchar(char const *str, size_t i, int *printf_res)
{
	ssize_t		count;

	count = write(1, str, i);
	*printf_res += (int) count;
}

void	ft_printf_putstr(char const *str, int *printf_res, t_flags flag)
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
	ft_printf_putchar(str, i, printf_res);
}
