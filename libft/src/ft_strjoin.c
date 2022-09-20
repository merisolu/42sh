/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:48:18 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/22 14:11:53 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns a new string, which is the result of combining s1 and s2. */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = ft_strnew(s1_len + s2_len);
	if (!result)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		result[i] = s1[i];
		i++;
	}
	while (i - s1_len < s2_len)
	{
		result[i] = s2[i - s1_len];
		i++;
	}
	result[s1_len + s2_len] = '\0';
	return (result);
}

/*
 * Returns a new string, which is the result of combining s1 and n chars
 * from s2. Returns NULL on error.
 */
char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	s2_len = ft_min_size_t(n, ft_strlen(s2));
	result = ft_strnew(s1_len + s2_len);
	if (!result)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		result[i] = s1[i];
		i++;
	}
	while (i - s1_len < s2_len)
	{
		result[i] = s2[i - s1_len];
		i++;
	}
	result[s1_len + s2_len] = '\0';
	return (result);
}
