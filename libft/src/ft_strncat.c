/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:01:14 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/23 15:09:38 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Appends a copy of s2 to s1, provided that s1 has enough space to do it.
 * Copies no more than n chars, and adds a null terminator at the end. */
char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	start;
	size_t	i;

	start = ft_strlen(s1);
	i = 0;
	while (i < n && s2[i] != '\0')
	{
		s1[start + i] = s2[i];
		i++;
	}
	s1[start + i] = '\0';
	return (s1);
}
