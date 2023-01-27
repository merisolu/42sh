/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:05:55 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/27 17:53:56 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	manage_quotes(t_token *original, t_state *state, char **result)
{
	if (!state->in_quotes)
	{
		state->in_quotes = true;
		state->quote_type = original->type;
	}
	else if (original->type == state->quote_type)
		state->in_quotes = false;
	else
		return (add_to_result(result, original->value, state));
	if (original && original->previous
		&& (original->previous->type
			| (TOKEN_DOUBLE_QUOTE | TOKEN_SINGLE_QUOTE)))
		return (add_to_result(result, "", state));
	return (1);
}

static int	manage_braces(t_state *state, char **result)
{
	(void) result;
	(state->brace_count)--;
	if (state->brace_count == 0)
		state->in_braces = false;
	return (1);
}

int	check_literals(t_token **cursor, t_state *state, char **result)
{
	t_token	*original;

	//if (state->in_quotes)
	//	ft_printf("toki %s\n", (*cursor)->value);
//	ft_putendl(*result);
	original = *cursor;
	if (eat_token(cursor, TOKEN_WHITESPACE, original))
	{
		if (state->in_braces && !(state->in_quotes))
			return (add_to_result(result, " ", state));
		if (state->in_quotes)
			return (add_to_result(result, original->value, state));
		state->continue_previous_node = 0;
		return (1);
	}
	if (eat_token(cursor, TOKEN_DOUBLE_QUOTE | TOKEN_SINGLE_QUOTE, original))
		return (manage_quotes(original, state, result));
	if (eat_token(cursor, TOKEN_CURLY_CLOSED, original) && state->in_braces && !state->in_quotes)
		return (manage_braces(state, result));
	*cursor = original;
	if (eat_token(cursor, TOKEN_WORD, original))
		return (add_to_result(result, original->value, state));
	return (0);
}
