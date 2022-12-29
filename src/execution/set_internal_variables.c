/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_internal_variables.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:29:32 by amann             #+#    #+#             */
/*   Updated: 2022/12/29 11:49:33 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	set_internal_variables(char **var_list, t_state *state)
{
	size_t	i;
	size_t	len;
	char	*name;
	char	*value;

	i = 0;
	while (var_list[i])
	{
		len = valid_env_name_length(var_list[i]);
		name = ft_strndup(var_list[i], len);
		if (!name)
			return (false);
		value = ft_strchr(var_list[i], '=');
		value += 1;
		if (!env_set(name, value, &(state->intern)))
				return (false);

		if (env_get(name, state->exported))
		{
			if (!env_set(name, value, &(state->exported)))
				return (false);
		}
		if (env_get(name, state->env))
		{
			if (!env_set(name, value, &(state->env)))
				return (false);
		}
		ft_strdel(&name);
		i++;
	}
	return (true);
}
