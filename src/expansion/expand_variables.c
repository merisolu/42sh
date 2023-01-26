/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:26:38 by amann             #+#    #+#             */
/*   Updated: 2023/01/26 11:57:55 by amann            ###   ########.fr       */
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

int	expand_variable(t_token **cursor, t_state *state, char **res)
{
	t_token	*original;
	int		return_code;

	original = *cursor;
//	print_tokens(original);
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
	return (0);
}
