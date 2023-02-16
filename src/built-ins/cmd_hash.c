/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:34:40 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/16 11:53:08 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static int	print_flag_error(char flag)
{
	ft_dprintf(STDERR_FILENO, "42sh: hash: -%c: invalid option\n", flag);
	ft_dprintf(STDERR_FILENO, "hash: usage: hash [utility...] or hash -r\n");
	return (1);
}

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

static void	clear_hash_table(t_hash_entry ***table)
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
		clear_hash_table(&(state->hash_table));
	else if (args[1] && args[1][0] == '-')
		return (print_flag_error(args[1][1]));
	if (args[1])
	{
		i = ft_strequ(args[1], "-r");
		while (args[++i])
		{
			if (built_in_get(args[i]))
				continue ;
			if (path_exists(state)
				&& find_binary(args[i], state, &path, true) == 1)
				hash_table_add(args[i], path, &(state->hash_table), 0);
			else
				print_error(
					0, ERRTEMPLATE_DOUBLE_NAMED, "hash", args[i], "not found");
		}
	}
	else
		print_hash_table(state->hash_table);
	return (0);
}
