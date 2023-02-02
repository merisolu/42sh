/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:28:03 by amann             #+#    #+#             */
/*   Updated: 2023/02/02 11:53:27 by amann            ###   ########.fr       */
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

static void	handle_quotes(t_token **cursor, t_state *state)
{
	if (!state->in_quotes)
	{
		state->in_quotes = true;
		state->quote_type = (*cursor)->type;
	}
	else if ((*cursor)->type == state->quote_type)
		state->in_quotes = false;
	*cursor = (*cursor)->next;
}

void	set_braces_state(t_state *state)
{
	if (!state->in_quotes)
	{
		state->in_braces = true;
		(state->brace_count)++;
	}
	else if (state->in_quotes && state->quote_type == TOKEN_SINGLE_QUOTE)
	{
		state->in_squote_braces = true;
		(state->brace_sq_count)++;
	}
	else if (state->in_quotes && state->quote_type == TOKEN_DOUBLE_QUOTE)
	{
		state->in_dquote_braces = true;
		(state->brace_dq_count)++;
	}
}

void	move_cursor_to_end(t_token **cursor, t_state *state)
{
	while (*cursor)
	{
		if ((*cursor)->type == TOKEN_DOLLAR)
		{
			*cursor = (*cursor)->next;
			if ((*cursor)->type == TOKEN_CURLY_OPEN)
				(state->brace_count)++;
		}
		else if ((*cursor)->type == TOKEN_CURLY_CLOSED && !(state->in_quotes))
		{
			(state->brace_count)--;
			*cursor = (*cursor)->next;
			if (state->brace_count == 0)
			{
				state->in_braces = false;
				return ;
			}
		}
		else if ((*cursor)->type == TOKEN_CURLY_CLOSED && (state->in_dquote_braces) && (state->in_quotes))
		{
			(state->brace_dq_count)--;
			*cursor = (*cursor)->next;
			if (state->brace_dq_count == 0)
			{
				state->in_dquote_braces = false;
				return ;
			}
		}
		else if ((*cursor)->type & (TOKEN_DOUBLE_QUOTE | TOKEN_SINGLE_QUOTE))
			handle_quotes(cursor, state);
		else
			*cursor = (*cursor)->next;
	}
	return ;
}
