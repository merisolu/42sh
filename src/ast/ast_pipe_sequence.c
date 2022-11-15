/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe_sequence.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:55:17 by amann             #+#    #+#             */
/*   Updated: 2022/11/15 17:42:11 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static int	last_pipe(t_token **cursor)
{
	t_token	*reset;
	t_token	*check;

	reset = *cursor;
	eat_token(cursor, TOKEN_PIPE, reset);
	check = *cursor;
	while (check)
	{
		if (check->type == TOKEN_PIPE)
			return (FALSE);
		check = check->next;
	}
	return (TRUE);
}

static int	pipe_recursion(t_token **cursor, t_ast **node)
{
	if (last_pipe(cursor))
	{
		if (!ast_simple_command(cursor, &((*node)->right)))
			return (0);
		return (1);
	}
	if (!ast_pipe_sequence(cursor, &((*node)->right)))
		return (0);
	return (1);
}

int	ast_pipe_sequence(t_token **cursor, t_ast **node)
{
	t_token	*reset;

	if (!*cursor)
		return (0);
	reset = *cursor;
	*node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!node)
		return (print_error(ERR_MALLOC_FAIL, 0));
	(*node)->node_type = AST_PIPE_SEQUENCE;
	if (!ast_simple_command(cursor, &((*node)->left)))
		return (0);
	reset = *cursor;
	if (!*cursor || eat_token(cursor, TOKEN_SEMICOLON, reset))
		return (1);
	if (!pipe_recursion(cursor, node))
		return (0);
	if (*cursor && (*cursor)->type == TOKEN_SEMICOLON)
		*cursor = (*cursor)->next;
	return (1);
}
