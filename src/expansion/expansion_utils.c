/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:28:03 by amann             #+#    #+#             */
/*   Updated: 2023/01/27 14:55:04 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/*
 * Many of the extended parameter expansions require us to check if a var
 * exists, and has a value. Let's make a helper function to check those things:
 */

bool	var_exists_and_set(char *name, t_state *state)
{
	char	*val;

	val = env_get_or(name, NULL, state->intern);
	if (val)
		 return (ft_strlen(val));
	val = env_get_or(name, NULL, state->env);
//	ft_printf("%s\n", val);
	if (val)
		 return (ft_strlen(val));
	return (false);
}
