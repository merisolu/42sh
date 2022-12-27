/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:34:40 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/27 12:11:44 by jumanner         ###   ########.fr       */
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
	(void)state;
	if (!args[1])
	{
		print_hash_table(state->hash_table);
		return (0);
	}
	return (0);
}
