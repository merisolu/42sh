/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe_sequence.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:55:17 by amann             #+#    #+#             */
/*   Updated: 2022/11/22 18:29:54 by amann            ###   ########.fr       */
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
	if (!*cursor || read_token(cursor, TOKEN_SEMICOLON, reset)
		|| (read_token(cursor, TOKEN_AMPERSAND | TOKEN_PIPE, reset) && (ft_strlen(reset->value) == 2)))
	{
		if (read_token(cursor, TOKEN_AMPERSAND | TOKEN_PIPE, reset))
			(*node)->and_or = (*cursor)->type;
		eat_token(cursor, TOKEN_SEMICOLON | TOKEN_AMPERSAND | TOKEN_PIPE, reset);
		return (true);
	}
	if (!pipe_recursion(cursor, node))
		return (false);
	if (*cursor && ((*cursor)->type == TOKEN_SEMICOLON
			|| ((*cursor)->type == TOKEN_PIPE && ft_strlen((*cursor)->value) == 2)
			|| ((*cursor)->type == TOKEN_AMPERSAND && ft_strlen((*cursor)->value) == 2)))
	{
		if ((*cursor)->type == TOKEN_PIPE || (*cursor)->type == TOKEN_AMPERSAND)
			(*node)->and_or = (*cursor)->type;
		*cursor = (*cursor)->next;
	}
	return (true);
}
