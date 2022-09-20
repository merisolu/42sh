/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisempty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:49:44 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/29 15:56:28 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Checks if the given string is empty (zero length or all whitespace).
 */
int	ft_strisempty(const char *str)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	if (len == 0)
		return (1);
	i = 0;
	while (i < len)
	{
		if (!ft_is_whitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}
