/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_getters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:34:08 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/26 11:35:36 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

/*
 * Gets a specific entry from the hash table. Returns NULL if nothing was found.
 */

t_hash_entry	*hash_table_get(char *name, t_hash_entry **table)
{
	size_t				i;
	unsigned long long	source_hash;

	if (!table)
		return (NULL);
	source_hash = fnv1_hash(name);
	i = 0;
	while (table[i])
	{
		if (source_hash == table[i]->hash)
			return (table[i]);
		i++;
	}
	return (NULL);
}

/*
 * Gets the path of a specific entry from the hash table and increments the hit
 * counter. Returns NULL if nothing was found.
 */

char	*hash_table_get_path(char *name, t_hash_entry **table)
{
	t_hash_entry	*entry;

	entry = hash_table_get(name, table);
	if (entry)
	{
		entry->hits++;
		return (entry->path);
	}
	return (NULL);
}
