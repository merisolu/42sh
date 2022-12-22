/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_internal_variables.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:29:32 by amann             #+#    #+#             */
/*   Updated: 2022/12/22 13:45:46 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	set_internal_variables(char **var_list, t_state *state)
{
	size_t	i;
	size_t	len;
	char	*name;
	char	*value;

	if (!(state->intern))
		state->intern = (char **) ft_memalloc(sizeof(char *) * (INPUT_MAX_SIZE / 2));
	if (!(state->intern))
		return (print_error(false, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
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
		ft_strdel(&name);
		i++;
	}
	return (true);
}
