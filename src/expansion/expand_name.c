/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:26:29 by amann             #+#    #+#             */
/*   Updated: 2023/02/08 11:35:35 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static int	expand_name_helper(char **res, char *valid, t_state *state)
{
	if (env_get_or(valid, NULL, state->intern))
		return (add_to_result(
				res,
				env_get_or(valid, "", state->intern),
				state
			));
	return (add_to_result(
			res,
			env_get_or(valid, "", state->env),
			state
		));
}

int	expand_name(char *value, t_state *state, char **res)
{
	int		return_code;
	char	*valid;
	char	*temp;

	if (ft_strequ(value, "?"))
	{
		temp = ft_itoa(state->last_return_value);
		return_code = add_to_result(res, temp, state);
		free(temp);
		return (return_code);
	}
	if (valid_env_name_length(value) == 0)
		return (0);
	valid = ft_strsub(value, 0, valid_env_name_length(value));
	if (!valid)
		return (-1);
	return_code = expand_name_helper(res, valid, state);
	free(valid);
	return (return_code);
}
