/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:28:03 by amann             #+#    #+#             */
/*   Updated: 2023/02/06 11:22:30 by amann            ###   ########.fr       */
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
	if (val)
		return (ft_strlen(val));
	return (false);
}

static void	handle_quotes(t_token **cursor, t_state *state)
{
	if (!state->t.in_quotes)
	{
		state->t.in_quotes = true;
		state->t.quote_token_type = (*cursor)->type;
	}
	else if ((*cursor)->type == state->t.quote_token_type)
		state->t.in_quotes = false;
	*cursor = (*cursor)->next;
}

void	set_braces_state(t_state *state)
{
	if (!state->t.in_quotes)
	{
		state->t.in_braces = true;
		(state->t.brace_count)++;
	}
	else if (state->t.in_quotes
		&& state->t.quote_token_type == TOKEN_SINGLE_QUOTE)
	{
		state->t.in_squote_braces = true;
		(state->t.brace_sq_count)++;
	}
	else if (state->t.in_quotes
		&& state->t.quote_token_type == TOKEN_DOUBLE_QUOTE)
	{
		state->t.in_dquote_braces = true;
		(state->t.brace_dq_count)++;
	}
}

static bool	handle_closing_curly(t_token **cursor, t_state *state)
{
	if (!(state->t.in_quotes))
	{
		(state->t.brace_count)--;
		*cursor = (*cursor)->next;
		if (state->t.brace_count == 0)
		{
			state->t.in_braces = false;
			return (false);
		}
	}
	else if ((state->t.in_dquote_braces) && (state->t.in_quotes))
	{
		(state->t.brace_dq_count)--;
		*cursor = (*cursor)->next;
		if (state->t.brace_dq_count == 0)
		{
			state->t.in_dquote_braces = false;
			return (false);
		}
	}
	return (true);
}

void	move_cursor_to_end(t_token **cursor, t_state *state)
{
	while (*cursor)
	{
		if ((*cursor)->type == TOKEN_DOLLAR)
		{
			*cursor = (*cursor)->next;
			if ((*cursor)->type == TOKEN_CURLY_OPEN)
				(state->t.brace_count)++;
		}
		else if ((*cursor)->type == TOKEN_CURLY_CLOSED)
		{
			if (!handle_closing_curly(cursor, state))
				return ;
		}
		else if ((*cursor)->type & (TOKEN_DOUBLE_QUOTE | TOKEN_SINGLE_QUOTE))
			handle_quotes(cursor, state);
		else
			*cursor = (*cursor)->next;
	}
	return ;
}
