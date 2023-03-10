/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:29:25 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/17 11:28:00 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copies at most len characters from src to dst. If there is room left in dst
 * the remainder of it is filled with \0. */
char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	int		reached_src_end;

	i = 0;
	reached_src_end = 0;
	while (i < len)
	{
		if (!reached_src_end && src[i])
			dst[i] = src[i];
		else
		{
			reached_src_end = 1;
			dst[i] = '\0';
		}
		i++;
	}
	return (dst);
}
