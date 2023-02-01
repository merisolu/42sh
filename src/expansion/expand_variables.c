/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:26:38 by amann             #+#    #+#             */
/*   Updated: 2023/02/01 15:48:48 by amann            ###   ########.fr       */
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
//	int		return_code;
	//print_tokens(*cursor);

	param = (*cursor)->previous->previous;
	//we should only display the text from the offending token sequence in the error message
	if ((*cursor)->previous->type == TOKEN_COLON && (*cursor)->type == TOKEN_CURLY_CLOSED)
		return (print_error(-1, ERRTEMPLATE_NAMED, state->input_context.input, ERR_BAD_SUB));
//	ft_printf("var name = %s\n", param->value);
	//the cursor will be pointing to token after the colon/hash/percent
	//the parser will ensure that the token sequence will end with the closing brace

	//print_tokens(*cursor);
	//a plus means we expand to the alternative if the param exists and has a value
	//	ft_printf("%d %d\n", state->in_dquote_braces, state->in_quotes);
	if ((*cursor)->previous->type == TOKEN_COLON
		&& (*cursor)->type & (TOKEN_MINUS | TOKEN_PLUS | TOKEN_EQUALS | TOKEN_QUESTION_MARK))
		return (expand_plus_minus(cursor, state, res, param));

//	if ((*cursor)->previous->type == TOKEN_COLON && (*cursor)->type & (TOKEN_MINUS | TOKEN_PLUS))
//		return (expand_plus_minus(cursor, state, res, param));

	//pattern matching, hash works from the start of the string, percent from the end
	//One char means shortest matching pattern, two means the longest. However, we do not need
	//to concern ourselves with this, the shell does not incorporate globbing, so patterns will not
	//vary in length
	//first, we expand the param into a temp string
	//then we expand what follows the hash or percent token into another temp string
	//We then take the length of the expansion and compare it to the start or end of the expanded
	//param.
	//If it matches, we truncate that respective part of the string
	//We then append the result to res
	if ((*cursor)->previous->type & (TOKEN_HASH | TOKEN_PERCENT)
		&& (*cursor)->type != TOKEN_CURLY_CLOSED)
		return (expand_hash_percent(cursor, state, res, param));


	return (0);
}

int	expand_variable(t_token **cursor, t_state *state, char **res)
{
	t_token	*original;
	int		return_code;

	original = *cursor;
	if (eat_token(cursor, TOKEN_DOLLAR, original)
		&& eat_token(cursor, TOKEN_WORD, original))
	{
		return_code = expand_name(original->next->value, state, res);
		if (return_code == 0)
			*cursor = original;
		return (return_code);
	}
	if (eat_token(cursor, TOKEN_DOLLAR, original)
		&& eat_token(cursor, TOKEN_CURLY_OPEN, original)
		&& eat_token(cursor, TOKEN_WORD, original)
		&& eat_token(cursor, TOKEN_CURLY_CLOSED, original))
		return (expand_name(original->next->next->value, state, res));
	if (eat_token(cursor, TOKEN_DOLLAR, original)
		&& eat_token(cursor, TOKEN_CURLY_OPEN, original)
		&& eat_token(cursor, TOKEN_WORD, original)
		&& eat_token(cursor, (TOKEN_COLON | TOKEN_HASH | TOKEN_PERCENT), original))
		return (extended_expansions_control(cursor, state, res));
	if (eat_token(cursor, TOKEN_DOLLAR, original)
		&& eat_token(cursor, TOKEN_CURLY_OPEN, original)
		&& eat_token(cursor, TOKEN_HASH, original)
		&& eat_token(cursor, TOKEN_WORD, original)
		&& eat_token(cursor, TOKEN_CURLY_CLOSED, original))
		return (expand_to_value_len(original->next->next->next->value, state, res));
	return (0);
}
