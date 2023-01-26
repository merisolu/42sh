/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:12:01 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/26 11:50:20 by jumanner         ###   ########.fr       */
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
 * should have when put into the table. If the entry already exists, it is
 * reset. Returns true on success, false otherwise.
 */

bool	hash_table_add(char *name, char *path, t_hash_entry ***table, \
unsigned int hits)
{
	t_hash_entry	*entry;
	bool			old_entry;

	if (!(*table))
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE,
				"unable to update hash table: table has not been allocated"));
	entry = hash_table_get(name, *table);
	old_entry = entry != NULL;
	if (!old_entry)
	{
		entry = ft_memalloc(sizeof(t_hash_entry));
		if (!entry)
			return (false);
	}
	else
		free(entry->path);
	entry->hash = fnv1_hash(name);
	entry->path = path;
	entry->hits = hits;
	if (old_entry)
		return (true);
	if (!ft_add_to_null_array((void ***)table, entry))
		hash_entry_free(entry);
	return (entry != NULL);
}

/*
 * Frees the path inside the hash entry, then the entry itself. *entry is also
 * set to NULL.
 */

void	hash_entry_free(t_hash_entry *entry)
{
	free(entry->path);
	ft_memdel((void **)&(entry));
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
	while (table[i])
	{
		hash_entry_free(table[i]);
		i++;
	}
}
