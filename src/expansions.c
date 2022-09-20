/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:47:12 by jumanner          #+#    #+#             */
/*   Updated: 2022/09/20 14:52:16 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	is_in_assignment(t_state *state, char ***res)
{
	char	*previous;
	char	*first_equals;
	char	*last_equals;

	previous = (*res)[ft_null_array_len((void **)(*res)) - 1];
	first_equals = ft_strchr(previous, '=');
	last_equals = ft_strrchr(previous, '=');
	return (state->continue_previous_node && previous && first_equals
		&& first_equals != previous && first_equals == last_equals
		&& !ft_strchr(previous, '~'));
}

static int	expand_tilde_special(t_token **cursor, t_state *state, char ***res)
{
	t_token	*original;

	original = *cursor;
	if (expect_token(cursor, TOKEN_PLUS, original))
	{
		if (token_is_word_end(*cursor)
			|| ((*cursor)->type == TOKEN_LITERAL && (*cursor)->value[0] == '/'))
			return (add_to_result(res,
					env_get_or("PWD", "~+", state->env), state));
	}
	if (expect_token(cursor, TOKEN_MINUS, original))
	{
		if (token_is_word_end(*cursor)
			|| ((*cursor)->type == TOKEN_LITERAL && (*cursor)->value[0] == '/'))
			return (add_to_result(res,
					env_get_or("OLDPWD", "~-", state->env), state));
	}
	*cursor = original;
	if (!((*cursor)->value[0] == '/' || (!state->continue_previous_node
				&& ft_strchr(":/", (*cursor)->value[0]))))
		return (add_to_result(res, "~", state));
	return (0);
}

int	expand_tilde(t_token **cursor, t_state *state, char ***res)
{
	t_token	*original;
	int		special_result;

	original = *cursor;
	if (!expect_token(cursor, TOKEN_TILDE, original))
		return (0);
	if (state->has_seen_tilde_in_word && !state->in_assignment)
		return (add_to_result(res, "~", state));
	state->has_seen_tilde_in_word = 1;
	state->in_assignment = is_in_assignment(state, res);
	if (original->previous && original->previous->type == TOKEN_LITERAL)
	{
		if (!state->in_assignment)
			return (add_to_result(res, "~", state));
	}
	else if (!token_is_word_end(*cursor))
	{
		special_result = expand_tilde_special(cursor, state, res);
		if (special_result != 0)
			return (special_result);
	}
	if (*cursor && (*cursor)->value && !ft_strchr(":/ \t", (*cursor)->value[0]))
		return (add_to_result(res, "~", state));
	return (add_to_result(res, env_get_or("HOME", "~", state->env), state));
}

static int	expand_name(char *value, t_state *state, char ***res)
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

int	expand_variable(t_token **cursor, t_state *state, char ***res)
{
	t_token	*original;
	int		return_code;

	original = *cursor;
	if (expect_token(cursor, TOKEN_DOLLAR, original)
		&& expect_token(cursor, TOKEN_LITERAL, original))
	{
		return_code = expand_name(original->next->value, state, res);
		if (return_code == 0)
			*cursor = original;
		return (return_code);
	}
	if (expect_token(cursor, TOKEN_DOLLAR, original)
		&& expect_token(cursor, TOKEN_CURLY_OPEN, original)
		&& expect_token(cursor, TOKEN_LITERAL, original)
		&& expect_token(cursor, TOKEN_CURLY_CLOSED, original))
		return (add_to_result(res, env_get_or(original->next->next->value, "",
					state->env), state));
	return (0);
}
