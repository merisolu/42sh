/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:53:58 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/31 10:57:39 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Replaces first occurance of 'target' in 'src' with 'replacement'. The
 * resulting string is malloced (even if nothing is replaced) and should be
 * freed when no longer necessary. Returns NULL on malloc errors.
 */
char	*ft_strreplace(char *src, char *target, char *replacement)
{
	char	*result;
	char	*replacement_start;
	size_t	target_len;

	target_len = ft_strlen(target);
	replacement_start = ft_strstr(src, target);
	if (!replacement_start)
		return (ft_strdup(src));
	result = ft_strnew(ft_strlen(src) - target_len + ft_strlen(replacement));
	if (!result)
		return (NULL);
	ft_strncpy(result, src, replacement_start - src);
	ft_strcpy(result + ft_strlen(result), replacement);
	ft_strcpy(result + ft_strlen(result), replacement_start + target_len);
	return (result);
}
