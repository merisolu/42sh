/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:12:01 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/29 11:57:52 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

/*
 * Gets a specific entry from the hash table. Returns NULL if nothing was found.
 */

static t_hash_entry	*hash_table_get(char *name, t_hash_entry **table)
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
 * Allocates the first entry in the hash table.
 */

bool	hash_table_setup(t_hash_entry ***table)
{
	*table = ft_memalloc(sizeof(t_hash_entry *));
	return (*table != NULL);
}

/*
 * Adds an entry to the hash table. 'hits' specifies the hit count the entry
 * should have when put into the table. If the entry already exists, it is
 * reset. Returns true on success, false otherwise.
 */

bool	hash_table_add(char *name, char *path, t_hash_entry ***table, \
unsigned int hits)
{
	t_hash_entry	*entry;
	bool			new_entry;
	int				add_to_array_result;

	if (!(*table))
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE,
				"unable to update hash table: table has not been allocated"));
	entry = hash_table_get(name, *table);
	new_entry = entry != NULL;
	if (!new_entry)
	{
		entry = ft_memalloc(sizeof(t_hash_entry));
		if (!entry)
			return (false);
	}
	entry->hash = fnv1_hash(name);
	entry->path = path;
	entry->hits = hits;
	if (new_entry)
		return (true);
	add_to_array_result = ft_add_to_null_array((void ***)table, entry);
	if (!add_to_array_result)
		free(entry);
	return (add_to_array_result == 1);
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

/*
 * Frees all entries from the hash table. Does not free the table itself.
 */

void	hash_table_clear(t_hash_entry **table)
{
	size_t	i;

	if (!table)
		return ;
	i = 0;
	while ((table)[i])
	{
		free((table)[i]->path);
		i++;
	}
	ft_free_null_array_elements((void **)table);
}
