/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:07:00 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/23 15:08:30 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copies bytes from dst to src, in a non-destructive way that allows for src 
 * and dst to overlap. */
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src && n > 0)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (src < dst)
			((char *)dst)[n - i - 1] = ((char *)src)[n - i - 1];
		else
			((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}
