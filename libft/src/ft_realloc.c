/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:52:38 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/08 12:19:59 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *pointer, size_t size, size_t old_size)
{
	void	*new_pointer;

	if (size == 0)
		return (NULL);
	if (!pointer)
		return (malloc(size));
	new_pointer = malloc(size);
	if (!new_pointer)
		return (NULL);
	if (old_size > 0)
		ft_memcpy(new_pointer, pointer, old_size);
	free(pointer);
	return (new_pointer);
}
