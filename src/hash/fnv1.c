/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:42:07 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/28 11:42:24 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

long long	fnv1_hash(char *source)
{
	unsigned long long	hash;
	size_t				i;

	hash = FNV1_OFFSET;
	i = 0;
	while (source[i])
	{
		hash *= FNV1_PRIME;
		hash ^= source[i];
		i++;
	}
	return (hash);
}
