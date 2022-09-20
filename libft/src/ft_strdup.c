/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 11:45:11 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/23 15:09:12 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Calculates the string's length, uses that to malloc, and then copies
 * the source to the new string. */
char	*ft_strdup(const char *s1)
{
	char	*result;
	int		length;
	int		i;

	length = ft_strlen(s1);
	result = (char *) malloc(sizeof(char) * (length + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
