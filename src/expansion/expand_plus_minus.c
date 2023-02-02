/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_plus_minus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:19:14 by amann             #+#    #+#             */
/*   Updated: 2023/02/02 14:02:33 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static bool	handle_equals_helper(t_token *param, t_state *state, char **res)
{
	char	**var;

	var = env_get_pointer(param->value, state->env);
	if (var)
	{
		if (!env_set(param->value, *res, &(state->env)))
			return (false);
	}
	var = env_get_pointer(param->value, state->intern);
	if (var)
	{
		if (!env_set(param->value, *res, &(state->intern)))
			return (false);
	}
	return (true);
}

static bool	handle_equals(t_token *param, t_state *state, char **res)
{
	if (!env_get_pointer(param->value, state->env)
		&& !env_get_pointer(param->value, state->intern))
	{
		if (!env_set(param->value, *res, &(state->intern)))
			return (false);
	}
	else
	{
		if (!handle_equals_helper(param, state, res))
			return (false);
	}
	return (true);
}

static int	handle_minus_eq_qm(t_token **cursor, t_state *state, char **res, \
		t_token *param)
{
	bool	equals;
	bool	qm;

	equals = (*cursor)->previous->type == TOKEN_EQUALS;
	qm = (*cursor)->previous->type == TOKEN_QUESTION_MARK;
	if ((*cursor)->type == TOKEN_WHITESPACE)
		*cursor = (*cursor)->next;
	expansions_loop(cursor, state, res, true);
	if (equals && !handle_equals(param, state, res))
		return (0);
	if (qm)
	{
		print_error(0, ERRTEMPLATE_NAMED, param->value, *res);
		ft_strdel(res);
	}
	return (1);
}

int	expand_plus_minus(t_token **cursor, t_state *state, char **res, \
		t_token *param)
{
	int		return_code;
	int		minus_eq_qm;

	*cursor = (*cursor)->next;
	if (!cursor)
		return (1);
	minus_eq_qm = (TOKEN_MINUS | TOKEN_EQUALS | TOKEN_QUESTION_MARK);
	set_braces_state(state);
	if (((*cursor)->previous->type == TOKEN_PLUS
			&& var_exists_and_set(param->value, state))
		|| ((*cursor)->previous->type & minus_eq_qm
			&& !var_exists_and_set(param->value, state)))
		return (handle_minus_eq_qm(cursor, state, res, param));
	return_code = expand_name(param->value, state, res);
	move_cursor_to_end(cursor, state);
	return (return_code);
}
