/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_change.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:16:45 by amann             #+#    #+#             */
/*   Updated: 2023/01/17 17:17:40 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	check_path_change(char *const *args, t_state *state, int ret, bool unset)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if ((!unset && ft_strnequ(args[i], "PATH=", 5))
			|| (unset && ft_strequ(args[i], "PATH")))
		{
			hash_table_clear(state->hash_table);
			break ;
		}
		i++;
	}
	return (ret);
}
