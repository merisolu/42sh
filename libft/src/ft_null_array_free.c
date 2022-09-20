/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_null_array_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:38:21 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/09 13:58:14 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
 * Frees each element of the given null-terminated array, then the pointer to
 * the array. Returns NULL when done.
 */
void	*ft_free_null_array(void **array)
{
	if (!array)
		return (NULL);
	ft_free_null_array_elements(array);
	free(array);
	return (NULL);
}

/* 
 * Frees each element of the given null-terminated array, but not the pointer to
 * the array itself.
 */
void	ft_free_null_array_elements(void **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
}
