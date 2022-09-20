/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:06:55 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/28 10:29:22 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns a new string which is the given string s with the character
 * at index i removed. Returns NULL on error.
 */
char	*ft_strdelchar(const char *s, size_t i)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s);
	result = ft_strnew(len - 1);
	if (!result)
		return (NULL);
	if (s)
		ft_strncpy(result, s, i);
	if (s && s[i] && len > 0)
		ft_strncpy(result + i, s + i + 1, len - i);
	return (result);
}
