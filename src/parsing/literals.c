/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:05:55 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/02 12:30:50 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	manage_quotes(t_token *original, t_state *state, char **result)
{
	if (!state->in_quotes)
	{
		state->in_quotes = true;
		state->quote_type = original->type;
		if (state->quote_type == TOKEN_SINGLE_QUOTE)
			state->in_squotes = true;
	}
	else if (original->type == state->quote_type)
	{
		state->in_quotes = false;
		if (state->quote_type == TOKEN_SINGLE_QUOTE)
			state->in_squotes = false;
	}
	else if (original->type == TOKEN_SINGLE_QUOTE)
	{
		if (state->in_squotes)
			state->in_squotes = false;
		else
			state->in_squotes = true;
		return (add_to_result(result, original->value, state));
	}
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
//	ft_printf("braces: %d\n", state->in_braces);
	if (!(state->in_quotes) && state->in_braces && !(state->in_squote_braces)
		&& !(state->in_dquote_braces))
	{
	//	ft_putendl("1");
		(state->brace_count)--;
		if (state->brace_count == 0)
			state->in_braces = false;
	}
	else if (state->in_quotes && state->quote_type == TOKEN_SINGLE_QUOTE)
	{
	//	ft_putendl("2");
		(state->brace_sq_count)--;
		if (state->brace_sq_count == 0)
			state->in_squote_braces = false;
	}
	else if (state->in_quotes && state->quote_type == TOKEN_DOUBLE_QUOTE
			&& !(state->in_squotes))
	{
	//	ft_putendl("3");
		(state->brace_dq_count)--;
		if (state->brace_dq_count == 0)
			state->in_dquote_braces = false;
	}
	else
	{
//		ft_putendl("bonjour");
		add_to_result(result, "}", state);
//		ft_putendl(*result);
	}
//	(void) result;
	return (1);
}

int	check_literals(t_token **cursor, t_state *state, char **result)
{
	t_token	*original;

//	ft_printf("in quotes: %d | in braces: %d | %s\n", state->in_quotes,	state->in_braces, (*cursor)->value);
//	ft_putendl(*result);
	if (!cursor || !(*cursor))
		return (0);
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
	if (eat_token(cursor, TOKEN_CURLY_CLOSED, original))
		return (manage_close_braces(state, result));
	*cursor = original;
	if (eat_token(cursor, TOKEN_WORD, original))
		return (add_to_result(result, original->value, state));
	return (0);
}
