/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcharn_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:18:22 by jumanner          #+#    #+#             */
/*   Updated: 2023/10/10 15:55:15 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Writes the given character n times to the given file descriptor. */
void	ft_putcharn_fd(char c, int n, int fd)
{
	while (n > 0)
	{
		if (write(fd, &c, 1) == -1)
			return ;
		n--;
	}
}
