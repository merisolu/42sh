/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe_sequence.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:55:17 by amann             #+#    #+#             */
/*   Updated: 2022/12/08 15:35:53 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

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

static bool	pipe_recursion(t_token **cursor, t_ast **node, int recurs_count)
{
	if ((*cursor)->type == TOKEN_PIPE
		&& (!(*cursor)->next || !(*cursor)->previous))
		return (print_bool_sep_error(ERR_SYNTAX, *cursor, false));
	if (last_pipe(cursor))
	{
		if (!ast_simple_command(cursor, &((*node)->right)))
			return (false);
		return (true);
	}
	if (!ast_pipe_sequence(cursor, &((*node)->right), recurs_count))
		return (false);
	return (true);
}

/*
 * variable recurs_count is needed for logical operator handling. We only want
 * to add values to the root node so we increment it each time
 * recursion happens and then check its value before updating the node
 */

bool	ast_pipe_sequence(t_token **cursor, t_ast **node, int recurs_count)
{
	t_token	*reset;

	if (!*cursor)
		return (false);
	*node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!*node)
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	(*node)->node_type = AST_PIPE_SEQUENCE;
	if (!ast_simple_command(cursor, &((*node)->left)))
		return (false);
	reset = *cursor;
	if (!*cursor || ast_is_separator(*cursor))
		return (check_end(cursor, reset, node));
	if (!pipe_recursion(cursor, node, ++recurs_count))
		return (false);
	return (recursion_end(cursor, reset, node, recurs_count));
}
