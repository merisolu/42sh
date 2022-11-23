/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe_sequence.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:55:17 by amann             #+#    #+#             */
/*   Updated: 2022/11/23 14:14:34 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "debug.h"

static bool	last_pipe(t_token **cursor)
{
	t_token	*reset;
	t_token	*check;

	reset = *cursor;
	eat_token(cursor, TOKEN_PIPE, reset);
	check = *cursor;
	while (check)
	{
		if (check->type == TOKEN_PIPE && ft_strlen(check->value) == 1)
			return (false);
		check = check->next;
	}
	return (true);
}

static bool	pipe_recursion(t_token **cursor, t_ast **node)
{
	if (last_pipe(cursor))
	{
		if (!ast_simple_command(cursor, &((*node)->right)))
			return (false);
		return (true);
	}
	if (!ast_pipe_sequence(cursor, &((*node)->right)))
		return (false);
	return (true);
}

//nb syntax error if more than 2 pipes or ampersands
//create a function called something like is_logic_op() to check the
//value of the token and make if checks shorter

bool	ast_pipe_sequence(t_token **cursor, t_ast **node)
{
	t_token	*reset;

	if (!*cursor)
		return (false);
	reset = *cursor;
	*node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!node)
		return (print_bool_error(ERR_MALLOC_FAIL, false));
	(*node)->node_type = AST_PIPE_SEQUENCE;
	if (!ast_simple_command(cursor, &((*node)->left)))
		return (false);
	reset = *cursor;
	if (!*cursor || ast_is_separator(*cursor))
	{
		(*node)->and_or = ast_is_logic_op(cursor, reset);
		return (true);
	}
	if (!pipe_recursion(cursor, node))
		return (false);
	if (*cursor && ast_is_separator(*cursor))
		(*node)->and_or = ast_is_logic_op(cursor, reset);
	return (true);
}
