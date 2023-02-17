/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching_control.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:34:43 by amann             #+#    #+#             */
/*   Updated: 2023/02/17 11:59:07 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	position_cursor(t_token **cursor, t_state *state, char **temp, \
		bool hash)
{
	if ((*cursor)->type == TOKEN_WHITESPACE)
	{
		*temp = ft_strdup((*cursor)->value);
		*cursor = (*cursor)->next;
		return ;
	}
	if (((*cursor)->type == TOKEN_HASH && hash)
		|| ((*cursor)->type == TOKEN_PERCENT && !hash))
	{
		*cursor = (*cursor)->next;
		state->t.last = true;
	}
}

/*
	pattern matching, hash works from the start of the string, percent from the
	end.

	One char means shortest matching pattern, two means the longest.
	However, we do not need	to concern ourselves with this, the shell does not
	incorporate globbing, so patterns will not vary in length.

	First, we expand the param into a temp string
	Then we expand what follows the hash or percent token into another temp
	string
	We then take the length of the expansion and compare it to the start or
	end of the expanded param.
	If it matches, we truncate that respective part of the string
	We then append the result to res
*/

int	pattern_matching_control(t_token **cursor, t_state *state, char **res, \
		t_token *param)
{
	char	*temp_res;
	char	*temp_exp;
	int		return_code;
	bool	hash;

	hash = (*cursor)->previous->type == TOKEN_HASH;
	temp_exp = NULL;
	position_cursor(cursor, state, &temp_exp, hash);
	temp_res = NULL;
	set_braces_state(state);
	expand_name(param->value, state, &temp_res);
	expansions_loop(cursor, state, &temp_exp, true);
	if (hash)
		handle_hash(state, temp_res, temp_exp);
	else
		handle_percent(state, temp_res, temp_exp);
	return_code = add_to_result(res, temp_res, state);
	free(temp_res);
	free(temp_exp);
	return (return_code);
}
