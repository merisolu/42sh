/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:47:12 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/24 19:28:41 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	return (expect_token(&cursor, TOKEN_WORD, cursor)
			&& expect_token(&cursor, TOKEN_EQUALS, cursor));
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
