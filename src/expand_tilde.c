/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:47:12 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/25 13:44:38 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//#include <pwd.h>


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

static int	check_colon(t_token *cursor)
{
	if (cursor && cursor->type != TOKEN_COLON)
		return (FALSE);
	cursor = cursor->previous;
	if (!cursor)
		return (FALSE);
	while (cursor->previous)
		cursor = cursor->previous;
	return (eat_token(&cursor, TOKEN_WORD, cursor)
			&& eat_token(&cursor, TOKEN_EQUALS, cursor));
}

/*
 * We can find the appropriate user directory using the passwd struct
 * Malloc protection happens in add_to_result (just returns -1 if value == NULL)
 * We need to do it like this to avoid leaking memory when constructing our string
 */

static int	find_user(char **res, t_token **cursor, t_state *state)
{
	int				ret;
	struct passwd	*pw;
	char			*usr;

	pw = getpwnam((*cursor)->value);
	if (!pw)
	{
		usr = ft_strjoin("~", (*cursor)->value);
		ret = add_to_result(res, usr, state);
		free(usr);
	}
	else
		ret = add_to_result(res, pw->pw_dir, state);
	*cursor = (*cursor)->next;
	return (ret);
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
		if (eat_token(cursor, TOKEN_TILDE, original)
			&& read_token(cursor, TOKEN_FWD_SLASH | TOKEN_COLON | TOKEN_NULL, original))
			return (add_to_result(res, env_get_or("HOME", "~", state->env), state));
		if (eat_token(cursor, TOKEN_TILDE, original)
			&& eat_token(cursor, TOKEN_PLUS, original)
			&& read_token(cursor, TOKEN_FWD_SLASH | TOKEN_COLON | TOKEN_NULL, original))
			return (add_to_result(res, env_get_or("PWD", "~+", state->env), state));
		if (eat_token(cursor, TOKEN_TILDE, original)
			&& eat_token(cursor, TOKEN_MINUS, original)
			&& read_token(cursor, TOKEN_FWD_SLASH | TOKEN_COLON | TOKEN_NULL, original))
			return (add_to_result(res, env_get_or("OLDPWD", "~-", state->env), state));
		if (eat_token(cursor, TOKEN_TILDE, original)
			&& read_token(cursor, TOKEN_WORD, original))
			return (find_user(res, cursor, state));
		}
	return (0);
}
