/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:46:00 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/23 15:09:25 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Appends src to the end of dst, up to dstsize - ft_strlen(dst) - 1 chars. 
 * Null terminates the result if possible, and returns the size of the
 * created string. */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_length;

	dst_length = ft_min_size_t(ft_strlen(dst), dstsize);
	i = 0;
	while (src[i] && dst_length + i + 1 < dstsize)
	{
		dst[dst_length + i] = src[i];
		i++;
	}
	if (dstsize != 0 && dst_length + i < dstsize)
		dst[dst_length + i] = '\0';
	return (dst_length + ft_strlen(src));
}
