/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:05:55 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/08 11:37:05 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	handle_single_quotes(t_token *original, t_state *state, \
		char **result)
{
	if (state->t.in_squotes)
		state->t.in_squotes = false;
	else
		state->t.in_squotes = true;
	return (add_to_result(result, original->value, state));
}

static int	manage_quotes(t_token *original, t_state *state, char **result)
{
	if (!state->t.in_quotes)
	{
		state->t.in_quotes = true;
		state->t.quote_token_type = original->type;
		if (state->t.quote_token_type == TOKEN_SINGLE_QUOTE)
			state->t.in_squotes = true;
	}
	else if (original->type == state->t.quote_token_type)
	{
		state->t.in_quotes = false;
		if (state->t.quote_token_type == TOKEN_SINGLE_QUOTE)
			state->t.in_squotes = false;
	}
	else if (original->type == TOKEN_SINGLE_QUOTE)
		return (handle_single_quotes(original, state, result));
	else
		return (add_to_result(result, original->value, state));
	if (original && original->previous
		&& (original->previous->type
			| (TOKEN_DOUBLE_QUOTE | TOKEN_SINGLE_QUOTE)))
		return (add_to_result(result, "", state));
	return (1);
}

static int	manage_close_braces(t_state *state, char **result)
{
	if (!(state->t.in_quotes) && state->t.in_braces
		&& !(state->t.in_squote_braces) && !(state->t.in_dquote_braces))
	{
		(state->t.brace_count)--;
		if (state->t.brace_count == 0)
			state->t.in_braces = false;
	}
	else if (state->t.in_quotes && state->t.brace_sq_count > 0
		&& state->t.quote_token_type == TOKEN_SINGLE_QUOTE)
	{
		(state->t.brace_sq_count)--;
		if (state->t.brace_sq_count == 0)
			state->t.in_squote_braces = false;
	}
	else if (state->t.in_quotes
		&& state->t.quote_token_type == TOKEN_DOUBLE_QUOTE
		&& !(state->t.in_squotes) && state->t.brace_dq_count > 0)
	{
		(state->t.brace_dq_count)--;
		if (state->t.brace_dq_count == 0)
			state->t.in_dquote_braces = false;
	}
	else
		add_to_result(result, "}", state);
	return (1);
}

int	check_literals(t_token **cursor, t_state *state, char **result)
{
	t_token	*original;

	if (!cursor || !(*cursor))
		return (0);
	original = *cursor;
	if (eat_token(cursor, TOKEN_WHITESPACE, original))
	{
		if (state->t.in_quotes)
			return (add_to_result(result, original->value, state));
		else
			return (add_to_result(result, " ", state));
		state->continue_previous_node = 0;
		return (1);
	}
	if (eat_token(cursor, TOKEN_DOUBLE_QUOTE | TOKEN_SINGLE_QUOTE, original))
		return (manage_quotes(original, state, result));
	if (eat_token(cursor, TOKEN_CURLY_CLOSED, original))
		return (manage_close_braces(state, result));
	*cursor = original;
	if (eat_token(cursor, TOKEN_WORD, original))
		return (add_to_result(result, original->value, state));
	return (0);
}
