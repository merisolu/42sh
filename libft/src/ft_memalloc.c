/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:33:36 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/23 15:07:46 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates the given amount of memory, then sets all bytes within that
 * allocated memory to zero and returns the result. */
void	*ft_memalloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (!result)
		return (NULL);
	ft_bzero(result, size);
	return (result);
}
