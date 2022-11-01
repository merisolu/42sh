/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:05:55 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/31 11:33:32 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_literals(t_token **cursor, t_state *state, char **result)
{
	t_token	*original;

	original = *cursor;
	if (eat_token(cursor, TOKEN_WHITESPACE, original))
	{
		if (state->in_quotes)
			return (add_to_result(result, original->value, state));
		state->continue_previous_node = 0;
		return (1);
	}
	if (eat_token(cursor, TOKEN_DOUBLE_QUOTE, original))
	{
		state->in_quotes = !state->in_quotes;
		if (original && original->previous
			&& original->previous->type == TOKEN_DOUBLE_QUOTE)
			return (add_to_result(result, "", state));
		return (1);
	}
	if (eat_token(cursor, TOKEN_WORD, original))
		return (add_to_result(result, original->value, state));
	return (0);
}
