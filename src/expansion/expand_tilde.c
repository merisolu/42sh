/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:47:12 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/25 14:20:49 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_first_equals(t_token *cursor)
{
	int	first;

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
 * Malloc protection happens in add_to_result
 * (just returns -1 if value == NULL)
 * We need to do it like this to avoid leaking memory when
 * constructing our string
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

int	expand_tilde(t_token **csr, t_state *s, char **res)
{
	t_token			*fb;
	t_token_type	scn;

	scn = TOKEN_FWD_SLASH | TOKEN_COLON | TOKEN_NULL;
	fb = *csr;
	if (fb->type != TOKEN_TILDE || ft_strlen(fb->value) > 1)
		return (0);
	if (!fb->previous || check_first_equals(fb->previous)
		|| check_colon(fb->previous))
	{
		if (eat_token(csr, TOKEN_TILDE, fb) && read_token(csr, scn, fb))
			return (add_to_result(res, env_get_or("HOME", "~", s->env), s));
		if (eat_token(csr, TOKEN_TILDE, fb) && eat_token(csr, TOKEN_PLUS, fb)
			&& read_token(csr, TOKEN_FWD_SLASH | TOKEN_COLON | TOKEN_NULL, fb))
			return (add_to_result(res, env_get_or("PWD", "~+", s->env), s));
		if (eat_token(csr, TOKEN_TILDE, fb) && eat_token(csr, TOKEN_MINUS, fb)
			&& read_token(csr, TOKEN_FWD_SLASH | TOKEN_COLON | TOKEN_NULL, fb))
			return (add_to_result(res, env_get_or("OLDPWD", "~-", s->env), s));
		if (eat_token(csr, TOKEN_TILDE, fb) && read_token(csr, TOKEN_WORD, fb))
			return (find_user(res, csr, s));
	}
	return (0);
}
