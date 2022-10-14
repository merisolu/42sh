/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:48:18 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/14 13:51:52 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns a new string, which is the result of combining s1 and s2. Frees s1
 * before returning the result (even if the join was not successful).
 *
 * Returns NULL on error.
 */
char	*ft_strjoinfree(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = ft_strnew(s1_len + s2_len);
	if (!result)
	{
		free((void *)s1);
		return (NULL);
	}
	ft_strncpy(result, s1, s1_len);
	ft_strncpy(result + s1_len, s2, s2_len);
	free((void *)s1);
	return (result);
}

/*
 * Returns a new string, which is the result of combining s1 and n chars
 * from s2. Frees s1 before returning the result (even if the join was
 * not successful).
 *
 * Returns NULL on error.
 */
char	*ft_strnjoinfree(char const *s1, char const *s2, size_t n)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_min_size_t(n, ft_strlen(s2));
	result = ft_strnew(s1_len + s2_len);
	if (!result)
	{
		free((void *)s1);
		return (NULL);
	}
	ft_strncpy(result, s1, s1_len);
	ft_strncpy(result + s1_len, s2, s2_len);
	free((void *)s1);
	return (result);
}
