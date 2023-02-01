/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_to_value_len.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:10:29 by amann             #+#    #+#             */
/*   Updated: 2023/02/01 17:14:48 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

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

	if (cursor && *cursor && (*cursor)->type != TOKEN_WORD
		&& (*cursor)->next && (*cursor)->next->type != TOKEN_CURLY_CLOSED)
	{
		print_error(0, ERRTEMPLATE_NAMED, (*cursor)->value, ERR_BAD_SUB);
		move_cursor_to_end(cursor, state);
		return (0);
	}
	name = (*cursor)->value;
	temp = NULL;
	expand_name(name, state, &temp);
	temp2 = ft_itoa((int)ft_strlen(temp));
	if (!temp2)
		return (print_error(0, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	return_code = add_to_result(res, temp2, state);
	free(temp);
	free(temp2);
	move_cursor_to_end(cursor, state);
	return (return_code);
}
