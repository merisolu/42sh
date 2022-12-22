/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:34:40 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/21 13:58:21 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static long long	fnv1_hash(char *source)
{
	unsigned long long	hash;
	size_t				i;

	hash = (unsigned long long) HASH_FNV1_OFFSET;
	i = 0;
	while (source[i])
	{
		hash *= (unsigned long long) HASH_FNV1_PRIME;
		hash ^= (unsigned long long) HASH_FNV1_OFFSET;
		i++;
	}
	return (hash);
}

int	cmd_hash(char *const *args, t_state *state)
{
	(void)state;
	if (!args[1])
	{
		ft_printf("No args.\n");
		return (0);
	}
	ft_printf("Result: %llu\n", fnv1_hash(args[1]));
	return (0);
}
