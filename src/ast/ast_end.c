/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:42:43 by amann             #+#    #+#             */
/*   Updated: 2023/01/11 14:02:12 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static bool	handle_logic_ops(t_token **cursor, t_ast **node)
{
	if (ast_is_logic_op(cursor))
	{
		if (!(*cursor)->next || !((*node)->left->left))
			return (false);
		(*node)->and_or = (*cursor)->type;
	}
	return (true);
}

bool	recursion_end(t_token **cursor, t_token *reset, t_ast **node, int rc)
{
	if (*cursor && ast_is_separator(*cursor) && rc == 1)
	{
		if (!handle_logic_ops(cursor, node))
			return (print_bool_sep_error(ERR_SYNTAX, *cursor, false));
		if (*cursor)
			(*node)->amp = (ft_strequ((*cursor)->value, "&") != 0);
		eat_token(
			cursor,
			TOKEN_AMPERSAND | TOKEN_PIPE | TOKEN_SEMICOLON,
			reset
			);
	}
	return (true);
}

bool	check_end(t_token **cursor, t_token *reset, t_ast **node)
{
	if (!((*node)->left->left))
		return (print_bool_sep_error(ERR_SYNTAX, *cursor, false));
	if (!handle_logic_ops(cursor, node))
		return (print_bool_sep_error(ERR_SYNTAX, *cursor, false));
	if (*cursor)
		(*node)->amp = (ft_strequ((*cursor)->value, "&") != 0);
	eat_token(
		cursor,
		TOKEN_AMPERSAND | TOKEN_PIPE | TOKEN_SEMICOLON,
		reset
		);
	return (true);
}
