/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:52:45 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/08 09:44:21 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Uses ft_memcpy to copy the string from src to dst (including the null
 * at the end). */
char	*ft_strcpy(char *dst, const char *src)
{
	ft_memcpy(dst, src, ft_strlen(src) + 1);
	return (dst);
}
