/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:10:50 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/28 11:44:04 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

/* Includes */

# include "libft.h"
# include "general.h"

/* Defines */

# define FNV1_OFFSET 0xCBF29CE484222325
# define FNV1_PRIME 0x00000100000001B3

/* Files */

/* hash_table.c */
bool		hash_table_setup(t_hash_entry ***table);
bool		hash_table_add(char *key, char *path, t_hash_entry ***table, \
unsigned int hits);
char		*hash_table_get(char *source, t_hash_entry **table);
void		hash_table_clear(t_hash_entry **table);

/* fvn1.c */
long long	fnv1_hash(char *source);

#endif