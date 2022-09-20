/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 11:13:04 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/01 15:49:11 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Calculates the length of the given string. */
size_t	ft_strlen(const char *s)
{
	size_t	result;

	if (!s)
		return (0);
	result = 0;
	while (s[result])
		result++;
	return (result);
}

/* Calculates the length of the given string. */
int	ft_strlen_int(const char *s)
{
	int	result;

	if (!s)
		return (0);
	result = 0;
	while (s[result])
		result++;
	return (result);
}
