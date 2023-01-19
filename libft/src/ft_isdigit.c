/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 10:22:23 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/19 11:02:51 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns true if the given char is a digit. */
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*
 * Returns true if the given string is all digits.
 */
bool	ft_isdigit_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}
