/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_to_value_len.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:10:29 by amann             #+#    #+#             */
/*   Updated: 2023/02/15 18:05:31 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static int	malloc_err(t_state *state)
{
	if (!(state->t.autocomp))
		return (print_error(0, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	return (0);
}

static int	bad_sub(t_state *state, t_token **cursor)
{
	set_braces_state(state);
	if (!(state->t.autocomp))
		print_error(0, ERRTEMPLATE_NAMED, state->t.expansion_word,
			ERR_BAD_SUB);
	move_cursor_to_end(cursor, state);
	return (0);
}
/*
 * One of the simpler expansions, we find the length of the value of the
 * variable referred to by "name", and print that. If the variable cannot
 * be found, we just print 0.
 */

int	expand_to_value_len(t_token **cursor, t_state *state, char **res)
{
	char	*temp;
	char	*temp2;
	char	*name;
	int		return_code;

	if (!cursor || !(*cursor) || !((*cursor)->next)
		|| (*cursor)->type != TOKEN_WORD
		|| (*cursor)->next->type != TOKEN_CURLY_CLOSED)
		return (bad_sub(state, cursor));
	name = (*cursor)->value;
	temp = NULL;
	expand_name(name, state, &temp);
	temp2 = ft_itoa((int)ft_strlen(temp));
	if (!temp2)
		return (malloc_err(state));
	return_code = add_to_result(res, temp2, state);
	free(temp);
	free(temp2);
	move_cursor_to_end(cursor, state);
	return (return_code);
}
