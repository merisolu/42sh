/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_read_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:59:39 by amann             #+#    #+#             */
/*   Updated: 2022/10/27 14:14:37 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
 * Checks if the cursor is currently on a token with the type of 'type'.
 *
 * If it is, the cursor is advanced to (*cursor)->next, and 1 is returned.
 *
 * If not, *cursor is set to on_fail, and 0 is returned. This is also done
 * if cursor or *cursor is NULL.
 *
 * The goal was to have a "chainable function" that could be called repeatedly
 * to check if a set of tokens in a list matches a predetermined set, while also
 * allowing for easy resets to the start of the chain (for immediate checking of
 * another sequence of tokens) without having to handle it in the calling
 * function.
 */
int	eat_token(t_token **cursor, t_token_type type, t_token *on_fail)
{
	int	result;

	if (!cursor || !(*cursor))
	{
		if (cursor)
		{
			if (type & TOKEN_NULL)
				return (TRUE);
			*cursor = on_fail;
		}
		return (FALSE);
	}
	result = (*cursor)->type & type;
	if (result)
		(*cursor) = (*cursor)->next;
	else
		(*cursor) = on_fail;
	return (result);
}

int	read_token(t_token **cursor, t_token_type type, t_token *on_fail)
{
	int	result;

	if (!cursor || !(*cursor))
	{
		if (cursor)
		{
			if (type & TOKEN_NULL)
				return (TRUE);
			*cursor = on_fail;
		}
		return (FALSE);
	}
	result = (*cursor)->type & type;
	if (!result)
		(*cursor) = on_fail;
	return (result);
}
