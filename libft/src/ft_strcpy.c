/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:52:45 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/01 13:27:03 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Uses ft_memcpy to copy the string from src to dst (including the null
 * at the end). */
char	*ft_strcpy(char *dst, const char *src)
{
	if (!dst)
		return (dst);
	if (!src)
	{
		dst[0] = '\0';
		return (dst);
	}
	ft_memcpy(dst, src, ft_strlen(src) + 1);
	return (dst);
}
