/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:34:40 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/17 18:20:47 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static void	print_hash_table(t_hash_entry **table)
{
	size_t	i;

	if (!table)
	{
		ft_printf("hash: hash table not allocated\n");
		return ;
	}
	if (!table[0])
	{
		ft_printf("hash: hash table empty\n");
		return ;
	}
	ft_printf("hits\tcommand\n");
	i = 0;
	while (table[i])
	{
		ft_printf("%4i\t%s\n", table[i]->hits, table[i]->path);
		i++;
	}
}

static void	clear_hash_stable(t_hash_entry ***table)
{
	hash_table_clear(*table);
	free(*table);
	hash_table_setup(table);
	if (!(*table))
		print_error(0, ERRTEMPLATE_NAMED, "hash", ERR_MALLOC_FAIL);
}

int	cmd_hash(char *const *args, t_state *state)
{
	size_t	i;
	char	*path;

	if (ft_strequ(args[1], "-r"))
		clear_hash_stable(&(state->hash_table));
	if (args[1])
	{
		i = 1 + (ft_strequ(args[1], "-r") || args[2]);
		while (args[i])
		{
			if (path_exists(state)
				&& find_binary(args[i], state, &path, true) == 1)
				hash_table_add(args[i], path, &(state->hash_table), 0);
			else
				print_error(
					0, ERRTEMPLATE_DOUBLE_NAMED, "hash", args[i], "not found");
			i++;
		}
	}
	else
		print_hash_table(state->hash_table);
	return (0);
}
