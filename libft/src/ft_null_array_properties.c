/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_null_array_properties.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:19:56 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/06 12:20:13 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns the length of a null-terminated array.
 */
size_t	ft_null_array_len(void **array)
{
	size_t	result;

	if (!array || !(*array))
		return (0);
	result = 0;
	while (array[result])
		result++;
	return (result);
}
