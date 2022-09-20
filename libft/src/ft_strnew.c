/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:25:17 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/23 15:09:56 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates enough space for a new string of length size, sets all chars in
 * the string to \0 and then returns a pointer to it. */
char	*ft_strnew(size_t size)
{
	char	*result;

	result = (char *)ft_memalloc(sizeof(char) * size + 1);
	if (!result)
		return (NULL);
	ft_strclr(result);
	return (result);
}
