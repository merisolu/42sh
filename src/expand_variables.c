/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:26:38 by amann             #+#    #+#             */
/*   Updated: 2022/10/24 19:27:20 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
