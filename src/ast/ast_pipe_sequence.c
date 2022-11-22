/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe_sequence.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:55:17 by amann             #+#    #+#             */
/*   Updated: 2022/11/22 18:05:11 by amann            ###   ########.fr       */
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
//	ft_putendl("bonjour");
//	print_tokens(*cursor);
	if (!ast_simple_command(cursor, &((*node)->left)))
		return (false);
	reset = *cursor;
	if (!*cursor || read_token(cursor, TOKEN_SEMICOLON, reset)
		|| (read_token(cursor, TOKEN_AMPERSAND | TOKEN_PIPE, reset) && (ft_strlen(reset->value) == 2)))
	{
		ft_putendl("tassa");
		eat_token(cursor, TOKEN_SEMICOLON | TOKEN_AMPERSAND | TOKEN_PIPE, reset);
		return (true);
	}
	//*cursor = reset;
	if (!pipe_recursion(cursor, node))
		return (false);
//	print_tokens(*cursor);
	if (*cursor && ((*cursor)->type == TOKEN_SEMICOLON
			|| ((*cursor)->type == TOKEN_PIPE && ft_strlen((*cursor)->value) == 2)
			|| ((*cursor)->type == TOKEN_AMPERSAND && ft_strlen((*cursor)->value) == 2)))
	{
		*cursor = (*cursor)->next;
	}
	ft_putendl("tassa");
	return (true);
}
