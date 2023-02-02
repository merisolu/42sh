/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:26:38 by amann             #+#    #+#             */
/*   Updated: 2023/02/02 14:10:05 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/*
 * 
 *
 */

int	extended_expansions_control(t_token **cursor, t_state *state, char **res)
{
	t_token	*param;

	param = (*cursor)->previous->previous;
	if ((*cursor)->previous->type == TOKEN_COLON
		&& (*cursor)->type == TOKEN_CURLY_CLOSED)
		return (print_error(-1, ERRTEMPLATE_NAMED, state->input_context.input,
				ERR_BAD_SUB));
	if ((*cursor)->previous->type == TOKEN_COLON
		&& (*cursor)->type & \
		(TOKEN_MINUS | TOKEN_PLUS | TOKEN_EQUALS | TOKEN_QUESTION_MARK))
		return (expand_plus_minus(cursor, state, res, param));
	if ((*cursor)->previous->type & (TOKEN_HASH | TOKEN_PERCENT)
		&& (*cursor)->type != TOKEN_CURLY_CLOSED)
		return (expand_hash_percent(cursor, state, res, param));
	return (0);
}

int	check_extended_expansions(t_token **cursor, t_state *state, char **res)
{
	t_token	*original;

	original = *cursor;
	if (eat_token(cursor, TOKEN_DOLLAR, original)
		&& eat_token(cursor, TOKEN_CURLY_OPEN, original)
		&& eat_token(cursor, TOKEN_WORD, original)
		&& eat_token(cursor, (TOKEN_COLON | TOKEN_HASH | TOKEN_PERCENT),
			original))
		return (extended_expansions_control(cursor, state, res));
	if (eat_token(cursor, TOKEN_DOLLAR, original)
		&& eat_token(cursor, TOKEN_CURLY_OPEN, original)
		&& eat_token(cursor, TOKEN_HASH, original))
		return (expand_to_value_len(cursor, state, res));
	return (0);
}

int	expand_variable(t_token **cursor, t_state *state, char **res)
{
	t_token	*original;
	int		return_code;

	original = *cursor;
	if (eat_token(cursor, TOKEN_DOLLAR, original)
		&& eat_token(cursor, TOKEN_WORD | TOKEN_QUESTION_MARK, original))
	{
		return_code = expand_name(original->next->value, state, res);
		if (return_code == 0)
			*cursor = original;
		return (return_code);
	}
	if (eat_token(cursor, TOKEN_DOLLAR, original)
		&& eat_token(cursor, TOKEN_CURLY_OPEN, original)
		&& eat_token(cursor, TOKEN_WORD | TOKEN_QUESTION_MARK, original)
		&& eat_token(cursor, TOKEN_CURLY_CLOSED, original))
		return (expand_name(original->next->next->value, state, res));
	return (check_extended_expansions(cursor, state, res));
}
