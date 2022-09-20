/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:26:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/09 13:59:11 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Frees each element of the array, then the pointer to the array. Returns NULL
 * when done. */
void	*ft_free_array(void **array, size_t size)
{
	ft_free_array_elements(array, size);
	free(array);
	return (NULL);
}

/*
 * Frees each element of the given array, but not the pointer to
 * the array itself.
 */
void	ft_free_array_elements(void **array, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
}
