/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:54:19 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/27 14:34:55 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Creates a new string, with the given character c inserted to
 * index i of string s.
 */
char	*ft_strins(const char *s, size_t i, char c)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s);
	result = ft_strnew(len + 1);
	if (!result)
		return (NULL);
	if (s)
		ft_strncpy(result, s, i);
	result[i] = c;
	if (s && s[i] && len > 0)
		ft_strncpy(result + i + 1, s + i, len - i);
	return (result);
}
