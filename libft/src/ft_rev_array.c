/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 13:46:23 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/24 13:40:36 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_rev_array(void **array, size_t size)
{
	size_t	i;
	void	*temp;

	i = 0;
	while (i < size / 2)
	{
		temp = array[i];
		array[i] = array[size - 1 - i];
		array[size - 1 - i] = temp;
		i++;
	}
}

void	ft_rev_null_array(void **array)
{
	size_t	i;
	size_t	size;
	void	*temp;

	i = 0;
	size = ft_null_array_len(array);
	while (i < size / 2)
	{
		temp = array[i];
		array[i] = array[size - i - 1];
		array[size - i - 1] = temp;
		i++;
	}
}
