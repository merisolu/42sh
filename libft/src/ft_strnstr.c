/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:22:16 by jumanner          #+#    #+#             */
/*   Updated: 2022/01/20 13:44:52 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
 * Attempts to locate the first occurance of string n (needle)
 * in string stack (haystack), limiting the search to len chars in stack.
*/
char	*ft_strnstr(const char *stack, const char *n, size_t len)
{
	size_t	haystack_i;
	size_t	needle_i;

	if (ft_strlen(n) == 0)
		return ((char *)(stack));
	haystack_i = 0;
	len = ft_min_size_t(ft_strlen(stack), len);
	while (haystack_i < len)
	{
		needle_i = 0;
		while (n[needle_i])
		{
			if (needle_i + haystack_i >= len)
				return (NULL);
			needle_i++;
			if (n[needle_i - 1] != stack[haystack_i + needle_i - 1])
				break ;
		}
		if (n[needle_i - 1] == stack[haystack_i + needle_i - 1])
			return (((char *)(stack)) + haystack_i);
		haystack_i++;
	}
	return (NULL);
}
