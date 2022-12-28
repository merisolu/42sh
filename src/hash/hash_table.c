/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:12:01 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/28 11:43:34 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

/*
 * Allocates the first entry in the hash table.
 */

bool	hash_table_setup(t_hash_entry ***table)
{
	*table = ft_memalloc(sizeof(t_hash_entry *));
	return (*table != NULL);
}

/*
 * Adds an entry to the hash table. 'hits' specifies the hit count the entry
 * should have when put into the table. Returns true on success, false
 * otherwise.
 */

bool	hash_table_add(char *key, char *path, t_hash_entry ***table, \
unsigned int hits)
{
	t_hash_entry	*entry;
	int				add_to_array_result;

	entry = ft_memalloc(sizeof(t_hash_entry));
	if (!entry)
		return (false);
	entry->hash = fnv1_hash(key);
	entry->path = path;
	entry->hits = hits;
	add_to_array_result = ft_add_to_null_array((void ***)table, entry);
	if (!add_to_array_result)
	{
		free(entry);
		return (false);
	}
	return (true);
}

/*
 * Gets a specific entry from the hash table. Returns NULL if nothing was found.
 */

char	*hash_table_get(char *source, t_hash_entry **table)
{
	size_t				i;
	unsigned long long	source_hash;

	source_hash = fnv1_hash(source);
	i = 0;
	while (table[i])
	{
		if (source_hash == table[i]->hash)
		{
			table[i]->hits++;
			return (table[i]->path);
		}
		i++;
	}
	return (NULL);
}

/*
 * Frees all entries from the hash table. Does not free the table itself.
 */

void	hash_table_clear(t_hash_entry **table)
{
	size_t	i;

	i = 0;
	while ((table)[i])
	{
		free((table)[i]->path);
		i++;
	}
	ft_free_null_array_elements((void **)table);
}
