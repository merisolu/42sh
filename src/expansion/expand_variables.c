/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:26:38 by amann             #+#    #+#             */
/*   Updated: 2023/01/27 16:18:57 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static int	expand_name_helper(char **res, char *valid, t_state *state)
{
	if (env_get_or(valid, NULL, state->intern))
		return (add_to_result(
				res,
				env_get_or(valid, "", state->intern),
				state
			));
	return (add_to_result(
			res,
			env_get_or(valid, "", state->env),
			state
		));
}

static int	expand_name(char *value, t_state *state, char **res)
{
	int		return_code;
	char	*valid;
	char	*temp;

	//this will probably have to be handled in a separate function
	if (ft_strequ(value, "?"))
	{
		temp = ft_itoa(state->last_return_value);
		return_code = add_to_result(res, temp, state);
		free(temp);
		return (return_code);
	}
	if (valid_env_name_length(value) == 0)
		return (0);
	valid = ft_strsub(value, 0, valid_env_name_length(value));
	if (!valid)
		return (-1);
	return_code = expand_name_helper(res, valid, state);
	if (return_code == 1)
		add_to_result(res, value + valid_env_name_length(value), state);
	free(valid);
	return (return_code);
}

/*
 * 
 *
 */

int	extended_expansions_control(t_token **cursor, t_state *state, char **res)
{
	t_token	*param;
	//print_tokens(*cursor);

	param = (*cursor)->previous->previous;
	//we should only display the text from the offending token sequence in the error message
	if ((*cursor)->previous->type == TOKEN_COLON && (*cursor)->type == TOKEN_CURLY_CLOSED)
		return (print_error(-1, ERRTEMPLATE_NAMED, state->input_context.input, ERR_BAD_SUB));
//	ft_printf("var name = %s\n", param->value);
	//the cursor will be pointing to token after the colon/hash/percent
	//the parser will ensure that the token sequence will end with the closing brace

	//a plus means we expand to the alternative if the param exists and has a value
	if ((*cursor)->previous->type == TOKEN_COLON && (*cursor)->type == TOKEN_PLUS)
	{
		*cursor = (*cursor)->next;
		state->in_braces = true;
		(state->brace_count)++;
		if (var_exists_and_set(param->value, state))
		{
			expansions_loop(cursor, state, res, false);
			return (1);
		}
		else
		{
			move_cursor_to_end(cursor, state);
			return (add_to_result(res, "", state));
		}

	}

	//with plus, minus, questionmark and equals we need to check first whether the param is valid before we decide
	//what to expand to. If we are indeed expanding the parameter, we can skip past the rest of the tokens
	//up to the closing curly brace.



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
	return (0);
}
