/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_plus_minus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:19:14 by amann             #+#    #+#             */
/*   Updated: 2023/01/31 16:01:19 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static bool handle_equals(t_token *param, t_state *state, char **res)
{
	char	**var;

	var = env_get_pointer(param->value, state->env);
	if (var)
	{
		if (!env_set(param->value, *res, &(state->env)))
			return (false);
	}
	var = env_get_pointer(param->value, state->intern);
	if (var)
	{
		if (!env_set(param->value, *res, &(state->intern)))
			return (false);
	}
	return (true);
}

int	expand_plus_minus(t_token **cursor, t_state *state, char **res, t_token *param)
{
	int		return_code;
	bool	equals;

	*cursor = (*cursor)->next;
	if (!cursor)
		return (1);
	set_braces_state(state);
	if (((*cursor)->previous->type == TOKEN_PLUS && var_exists_and_set(param->value, state))
		|| ((*cursor)->previous->type & (TOKEN_MINUS | TOKEN_EQUALS) && !var_exists_and_set(param->value, state)))
	{
		equals = (*cursor)->previous->type == TOKEN_EQUALS;
		if ((*cursor)->type == TOKEN_WHITESPACE)
			*cursor = (*cursor)->next;
		expansions_loop(cursor, state, res, true);
		if (equals)
		{
			if (!env_get_pointer(param->value, state->env) && !env_get_pointer(param->value, state->intern))
			{
				if (!env_set(param->value, *res, &(state->intern)))
					return (0);
			}
			else
			{
				if (!handle_equals(param, state, res))
					return (0);
			}
		}
		return (1);
	}
	return_code = expand_name(param->value, state, res);
	move_cursor_to_end(cursor, state);
	return (return_code);
}
