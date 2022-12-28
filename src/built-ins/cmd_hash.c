/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:34:40 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/28 11:26:19 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static void	print_hash_table(t_hash_entry **table)
{
	size_t	i;

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

int	cmd_hash(char *const *args, t_state *state)
{
	char	*path;

	if (ft_strequ(args[1], "-r"))
	{
		hash_table_clear(state->hash_table);
		free(state->hash_table);
		hash_table_setup(&(state->hash_table));
	}
	else if (args[1])
	{
		if (find_binary(args[1], state, &path) == 1)
			hash_table_add(args[1], path, &(state->hash_table), 0);
	}
	else
		print_hash_table(state->hash_table);
	return (0);
}
