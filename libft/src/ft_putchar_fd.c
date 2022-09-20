/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:18:22 by jumanner          #+#    #+#             */
/*   Updated: 2022/08/31 10:20:14 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Writes the given character to the given file descriptor. */
void	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1))
		return ;
}
