/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:26:38 by amann             #+#    #+#             */
/*   Updated: 2023/02/16 13:54:19 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

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
			if ((*cursor)->type == TOKEN_CURLY_CLOSED && !(state->t.autocomp))
				print_error(-1, ERRTEMPLATE_NAMED, state->t.expansion_word,
					ERR_BAD_SUB);
			else if ((*cursor)->type != TOKEN_WHITESPACE
				&& !(state->t.autocomp))
				print_error(-1, ERRTEMPLATE_EXPANSION_SYNTAX, param->value,
					(*cursor)->value, ERR_EXPANSION_SYNTAX, (*cursor)->value);
			else if (!(state->t.autocomp))
				print_error(-1, ERRTEMPLATE_EXPANSION_SYNTAX, param->value,
					(*cursor)->next->value, ERR_EXPANSION_SYNTAX,
					(*cursor)->next->value);
			move_cursor_to_end(cursor, state);
			return (false);
		}
	}
	return (true);
}

static int	bad_sub(t_token **cursor, t_state *state)
{
	if (!(state->t.autocomp))
		print_error(-1, ERRTEMPLATE_NAMED, state->t.expansion_word,
			ERR_BAD_SUB);
	while (*cursor)
		*cursor = (*cursor)->next;
	return (-1);
}

static int	extended_expansions_control(t_token **cursor, t_state *state, \
		char **res)
{
	t_token	*param;

	param = (*cursor)->previous->previous;
	if (!check_ext_exp_errors(cursor, state, param))
		return (-1);
	if ((*cursor)->previous->type == TOKEN_COLON
		&& (*cursor)->type & \
		(TOKEN_MINUS | TOKEN_PLUS | TOKEN_EQUALS | TOKEN_QUESTION_MARK))
		return (expand_plus_minus(cursor, state, res, param));
	if ((*cursor)->previous->type & (TOKEN_HASH | TOKEN_PERCENT))
		return (pattern_matching_control(cursor, state, res, param));
	return (bad_sub(cursor, state));
}

static int	check_extended_expansions(t_token **cursor, t_state *state, \
		char **res)
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
		return (bad_sub(cursor, state));
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
