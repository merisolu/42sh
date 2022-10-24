/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:47:12 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/24 19:11:21 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
/*
static int	is_in_assignment(t_state *state, char **res)
{
	char	*first_equals;
	char	*last_equals;


	first_equals = ft_strchr(*res, '=');


}

static int	expand_tilde_special(t_token **cursor, t_state *state, char **res)
{
	t_token	*original;

	original = *cursor;
	if (expect_token(cursor, TOKEN_PLUS, original))
	{
		if (token_is_word_end(*cursor)
			|| ((*cursor)->type == TOKEN_WORD && (*cursor)->value[0] == '/'))
			return (add_to_result(res,
					env_get_or("PWD", "~+", state->env), state));
	}
	if (expect_token(cursor, TOKEN_MINUS, original))
	{
		if (token_is_word_end(*cursor)
			|| ((*cursor)->type == TOKEN_WORD && (*cursor)->value[0] == '/'))
			return (add_to_result(res,
					env_get_or("OLDPWD", "~-", state->env), state));
	}
	*cursor = original;
	if (!((*cursor)->value[0] == '/' || (!state->continue_previous_node
				&& ft_strchr(":/", (*cursor)->value[0]))))
		return (add_to_result(res, "~", state));
	return (0);
}*/

static int	check_first_equals(t_token *cursor)
{
	int first;

	if ((cursor && cursor->type != TOKEN_EQUALS)
		|| (cursor && cursor->type == TOKEN_EQUALS
		&& (!cursor->previous || cursor->previous->type != TOKEN_WORD)))
		return (FALSE);
	first = TRUE;
	cursor = cursor->previous;
	while (cursor)
	{
		if (cursor->type == TOKEN_EQUALS)
			return (FALSE);
		cursor = cursor->previous;
	}
	return (first);
}

static int	expect_slash_null_colon(t_token **cursor, t_token *check, t_token *fall_back)
{
	if (check == NULL)
		return (TRUE);
	if (check->type == TOKEN_FWD_SLASH || check->type == TOKEN_COLON)
		return (TRUE);
	*cursor = fall_back;
	return (FALSE);
}

static int	check_colon(t_token *cursor)
{
	if (cursor && cursor->type != TOKEN_COLON)
		return (FALSE);
	cursor = cursor->previous;
	if (!cursor)
		return (FALSE);
	while (cursor->previous)
		cursor = cursor->previous;
	return (expect_token(&cursor, TOKEN_WORD, cursor) && expect_token(&cursor, TOKEN_EQUALS, cursor));
}


int	expand_tilde(t_token **cursor, t_state *state, char **res)
{
	t_token	*original;

	original = *cursor;
	if (original->type != TOKEN_TILDE || ft_strlen(original->value) > 1)
		return (0);
	if (!original->previous || check_first_equals(original->previous)
		|| check_colon(original->previous))
	{
		if (expect_token(cursor, TOKEN_TILDE, original)
			&& expect_slash_null_colon(cursor, original->next, original))
			return (add_to_result(res, env_get_or("HOME", "~", state->env), state));
		if (expect_token(cursor, TOKEN_TILDE, original)
			&& expect_token(cursor, TOKEN_PLUS, original)
			&& expect_slash_null_colon(cursor, original->next->next, original))
			return (add_to_result(res, env_get_or("PWD", "~+", state->env), state));
		if (expect_token(cursor, TOKEN_TILDE, original)
			&& expect_token(cursor, TOKEN_MINUS, original)
			&& expect_slash_null_colon(cursor, original->next->next, original))
			return (add_to_result(res, env_get_or("OLDPWD", "~-", state->env), state));
	}
	return (0);
}

static int	expand_name(char *value, t_state *state, char **res)
{
	int		return_code;
	char	*valid;
	char	*temp;

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
	return_code = add_to_result(res, env_get_or(valid, "", state->env), state);
	if (return_code == 1)
		add_to_result(res, value + valid_env_name_length(value), state);
	free(valid);
	return (return_code);
}

int	expand_variable(t_token **cursor, t_state *state, char **res)
{
	t_token	*original;
	int		return_code;

	original = *cursor;
	if (expect_token(cursor, TOKEN_DOLLAR, original)
		&& expect_token(cursor, TOKEN_WORD, original))
	{
		return_code = expand_name(original->next->value, state, res);
		if (return_code == 0)
			*cursor = original;
		return (return_code);
	}
	if (expect_token(cursor, TOKEN_DOLLAR, original)
		&& expect_token(cursor, TOKEN_CURLY_OPEN, original)
		&& expect_token(cursor, TOKEN_WORD, original)
		&& expect_token(cursor, TOKEN_CURLY_CLOSED, original))
			return (expand_name(original->next->next->value, state, res));
	return (0);
}
