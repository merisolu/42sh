/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrrcount.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:35:37 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/13 11:56:36 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns the amount of occurances of char c in the string str, starting from
 * index start and moving backwards to zero.
 */
size_t	ft_strchrrcount(char *str, char c, size_t start)
{
	size_t	i;
	size_t	result;

	result = 0;
	i = start;
	while (1)
	{
		if (str[i] == c)
			result++;
		if (i == 0)
			break ;
		i--;
	}
	return (result);
}
