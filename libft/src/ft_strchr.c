/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:18:53 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/30 17:02:05 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Attempts to locate the first c in s. Returns a pointer if successful, NULL
 * if no match was found. */
char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (((char *)(s)) + i);
		i++;
	}
	if (s[i] == (char)c)
		return (((char *)(s)) + i);
	else
		return (NULL);
}
