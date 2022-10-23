/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:05:55 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/23 15:42:19 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	check_literals(t_token **cursor, t_state *state, char **result)
{
	t_token	*original;

	original = *cursor;
	if (expect_token(cursor, TOKEN_WHITESPACE, original))
	{
		if (state->in_double_quotes)
			return (add_to_result(result, original->value, state));
		state->continue_previous_node = 0;
		state->has_seen_tilde_in_word = 0;
		state->in_assignment = 0;
		return (1);
	}
	if (expect_token(cursor, TOKEN_DOUBLE_QUOTE, original))
	{
		state->in_double_quotes = !state->in_double_quotes;
		if (original && original->previous
			&& original->previous->type == TOKEN_DOUBLE_QUOTE)
			return (add_to_result(result, "", state));
		return (1);
	}
	if (expect_token(cursor, TOKEN_WORD, original))
		return (add_to_result(result, original->value, state));
	return (0);
}
