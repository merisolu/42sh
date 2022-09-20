/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:48:50 by jumanner          #+#    #+#             */
/*   Updated: 2022/08/26 14:51:10 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
 * Returns the distance to the byte c in the string s. Returns max + 1 if
 * nothing was found in the given range.
 */
size_t	ft_dstchr(const char *s, char c, size_t max)
{
	size_t	result;

	result = 0;
	while (result < max && s[result] != c)
		result++;
	if (s[result] == c)
		return (result);
	return (max + 1);
}
