/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_null_array_element.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:45:00 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/20 10:45:26 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Increases the given null terminated array's size by one and adds
 * the provided element to the newly-created slot.
 *
 * One will be returned on success. Zero otherwise.
 */
int	ft_add_to_null_array(void ***array, void *new)
{
	size_t	new_len;

	new_len = ft_null_array_len(*array) + 1;
	if (!ft_resize_null_array(array, new_len))
		return (0);
	(*array)[new_len - 1] = new;
	return (1);
}

/*
 * Creates a new null terminated array using the given array as a base,
 * but with the specified removeable element removed.
 *
 * One will be returned on success. Zero otherwise.
 */
int	ft_remove_from_null_array(void ***array, void *removeable)
{
	void	**result;
	size_t	src_i;
	size_t	dst_i;

	result = (void **)ft_memalloc(sizeof(void *) * (ft_null_array_len(*array)));
	if (!result)
		return (0);
	src_i = 0;
	dst_i = 0;
	while ((*array)[src_i])
	{
		if ((*array)[src_i] == removeable)
		{
			src_i++;
			continue ;
		}
		result[dst_i] = (*array)[src_i];
		src_i++;
		dst_i++;
	}
	free(removeable);
	free(*array);
	(*array) = result;
	return (1);
}
