/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:26:38 by amann             #+#    #+#             */
/*   Updated: 2023/02/03 15:47:19 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/*
 * 
 *
 */

static bool	check_ext_exp_errors(t_token **cursor, t_state *state, \
		t_token *param)
{
	if ((*cursor)->previous->type == TOKEN_COLON)
	{
		if ((!((*cursor)->type & (TOKEN_MINUS | TOKEN_PLUS \
				| TOKEN_QUESTION_MARK | TOKEN_EQUALS | TOKEN_WHITESPACE \
				| TOKEN_WORD))) || ((*cursor)->type == TOKEN_WHITESPACE
				&& (*cursor)->next->type != TOKEN_WORD))
		{
			set_braces_state(state);
			if ((*cursor)->type == TOKEN_CURLY_CLOSED)
				print_error(-1, ERRTEMPLATE_NAMED, state->expansion_word,
					ERR_BAD_SUB);
			else if ((*cursor)->type != TOKEN_WHITESPACE)
				print_error(-1, ERRTEMPLATE_EXPANSION_SYNTAX, param->value,
					(*cursor)->value, ERR_EXPANSION_SYNTAX, (*cursor)->value);
			else
				print_error(-1, ERRTEMPLATE_EXPANSION_SYNTAX, param->value,
					(*cursor)->next->value, ERR_EXPANSION_SYNTAX,
					(*cursor)->next->value);
			move_cursor_to_end(cursor, state);
			return (false);
		}
	}
	return (true);
}

int	extended_expansions_control(t_token **cursor, t_state *state, char **res)
{
	t_token	*param;

	param = (*cursor)->previous->previous;
	if (!check_ext_exp_errors(cursor, state, param))
		return (-1);
	if ((*cursor)->previous->type == TOKEN_COLON && (*cursor)->type & \
		(TOKEN_WHITESPACE | TOKEN_WORD))
	{
		set_braces_state(state);
		move_cursor_to_end(cursor, state);
		return (expand_name(param->value, state, res));
	}
	if ((*cursor)->previous->type == TOKEN_COLON
		&& (*cursor)->type & \
		(TOKEN_MINUS | TOKEN_PLUS | TOKEN_EQUALS | TOKEN_QUESTION_MARK))
		return (expand_plus_minus(cursor, state, res, param));
	if ((*cursor)->previous->type & (TOKEN_HASH | TOKEN_PERCENT))
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
	if (eat_token(cursor, TOKEN_DOLLAR, original)
		&& eat_token(cursor, TOKEN_CURLY_OPEN, original))
	{
		print_error(-1, ERRTEMPLATE_NAMED, state->expansion_word, ERR_BAD_SUB);
		set_braces_state(state);
		move_cursor_to_end(cursor, state);
		return (-1);
	}
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
