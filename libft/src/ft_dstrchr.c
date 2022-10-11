/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:02:36 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/11 13:21:03 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
 * Returns the distance to the byte c in the string s (searches backwards).
 * Returns start + 1 if nothing was found in the given range.
 */
size_t	ft_dstrchr(const char *s, char c, size_t start)
{
	size_t	result;
	size_t	i;

	result = 0;
	i = start;
	while (i > 0 && s[i] != c)
	{
		result++;
		i--;
	}
	if (s[i] == c)
		return (result);
	return (start + 1);
}
