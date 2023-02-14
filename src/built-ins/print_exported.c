/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exported.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:27:40 by amann             #+#    #+#             */
/*   Updated: 2023/02/14 15:51:15 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static bool	print_invalid_flag_error(char flag)
{
	ft_dprintf(STDERR_FILENO,
		"bash: export: -%c: invalid option\n", flag);
	ft_dprintf(STDERR_FILENO,
		"export: usage: export [-p] [name[=value] ...]\n");
	return (true);
}

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
	else if (args[1][0] == '-')
		return (print_invalid_flag_error(args[1][1]));
	return (false);
}
