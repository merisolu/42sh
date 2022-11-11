/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:05:55 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/11 17:01:56 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	manage_quotes(t_token *original, t_state *state, char **result)
{
	if (!state->in_quotes)
	{
		state->in_quotes = TRUE;
		state->quote_type = original->type;
	}
	else if (original->type == state->quote_type)
		state->in_quotes = FALSE;
	else
		return (add_to_result(result, original->value, state));
	if (original && original->previous
		&& (original->previous->type
			| (TOKEN_DOUBLE_QUOTE | TOKEN_SINGLE_QUOTE)))
		return (add_to_result(result, "", state));
	return (1);
}

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
	if (eat_token(cursor, TOKEN_DOUBLE_QUOTE, original)
		|| eat_token(cursor, TOKEN_SINGLE_QUOTE, original))
		return (manage_quotes(original, state, result));
	if (eat_token(cursor, TOKEN_WORD, original))
		return (add_to_result(result, original->value, state));
	return (0);
}
