/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memichr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:48:05 by jumanner          #+#    #+#             */
/*   Updated: 2022/08/26 14:52:23 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Finds the first byte that's NOT c pointed to by s, as long as it
 * exists within n bytes, and returns a pointer to it. */
void	*ft_memichr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] != (unsigned char) c)
			return ((void *)(((unsigned char *)s) + i));
		i++;
	}
	return (NULL);
}
