/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exported.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:27:40 by amann             #+#    #+#             */
/*   Updated: 2023/01/04 14:33:40 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

bool	print_exported(char *const *args, t_state *state)
{
	int	i;

	if (!args[1] || (ft_strequ(args[1], "-p") && !args[2]))
	{
		i = 0;
		while (state->exported && (state->exported)[i])
		{
			if (ft_strchr((state->exported)[i], '='))
			{
				ft_printf("export %.*s=\"%s\"\n",
					valid_env_name_length((state->exported)[i]),
					(state->exported)[i],
					ft_strchr((state->exported)[i], '=') + 1);
			}
			else
				ft_printf("export %s\n", (state->exported)[i]);
			i++;
		}
		return (true);
	}
	return (false);
}
