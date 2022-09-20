/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelword.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:34:28 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/11 11:44:07 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns a new string, which is the result of deleting the word that ends at
 * the given index end from the given string *s. Returns NULL on error.
 *
 * The count of deleted characters will be stored in del_count, if it is
 * not NULL.
 */
char	*ft_strdelword(const char *s, size_t end, size_t *del_count)
{
	char	*result;
	size_t	start;
	size_t	len;

	len = ft_strlen(s);
	start = end;
	while (start > 0 && start < len && ft_is_whitespace(s[start]))
		start--;
	while (start > 0 && start < len && !ft_is_whitespace(s[start]))
		start--;
	result = ft_strnew(len - (end - start));
	if (!result)
		return (NULL);
	ft_strncpy(result, s, start);
	ft_strcpy(result + start, s + end + 1);
	if (del_count)
		*del_count = end - start + 1;
	return (result);
}
