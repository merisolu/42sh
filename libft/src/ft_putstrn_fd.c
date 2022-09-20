/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrn_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 10:48:27 by jumanner          #+#    #+#             */
/*   Updated: 2022/08/31 10:21:06 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Writes the given string up to n chars or until the null-byte to the given
 * file descriptor.
*/
void	ft_putstrn_fd(char const *s, const int n, int fd)
{
	int	i;

	i = 0;
	while (i < n && s[i])
	{
		if (write(fd, s + i, 1) == -1)
			return ;
		i++;
	}
}
