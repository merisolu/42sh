/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe_sequence.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:55:17 by amann             #+#    #+#             */
/*   Updated: 2022/11/01 15:24:09 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

static int	redirects_node(t_token **cursor, t_ast **node)
{
	if (!*cursor)
		return (1);
	if (!*node)
		*node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!*node)
		return (print_error(ERR_MALLOC_FAIL, 0));
	if (!(*node)->node_type)
		(*node)->node_type = AST_REDIRECTIONS;
	return (ast_redirect_control(*node, cursor));
}

static int	args_node(t_token **cursor, t_ast **node)
{
	if (!*cursor)
		return (1);
	if (!*node)
		*node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!*node)
		return (print_error(ERR_MALLOC_FAIL, 0));
	if (!(*node)->node_type)
		(*node)->node_type = AST_COMMAND_ARGS;
	if (!(*node)->arg_list)
		(*node)->arg_list = (char **) ft_memalloc(sizeof(char *) * 3);
	if (!(*node)->arg_list)
		return (print_error(ERR_MALLOC_FAIL, 0));
	if (!(allocate_args_array(&(*node)->arg_list, cursor)))
		return (print_error(ERR_MALLOC_FAIL, 0));
	return (1);
}

static t_ast	*simple_command(t_token **cursor)
{
	t_ast	*node;
	t_token	*reset;

	reset = *cursor;
	node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!node)
		return (print_error_ast(ERR_MALLOC_FAIL, NULL));
	node->node_type = AST_SIMPLE_COMMAND;
	while (*cursor)
	{
		if (!*cursor || read_token(cursor, TOKEN_SEMICOLON, reset)
			|| read_token(cursor, TOKEN_PIPE, reset))
			break ;
		if (!args_node(cursor, &node->left)
			|| !redirects_node(cursor, &node->right))
			return (NULL);
		reset = *cursor;
	}
	return (node);
}

t_ast	*ast_pipe_sequence(t_token **cursor)
{
	t_ast	*node;
	t_token	*reset;

	if (!*cursor)
		return (NULL);
	reset = *cursor;
	node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!node)
		return (print_error_ast(ERR_MALLOC_FAIL, NULL));
	node->node_type = AST_PIPE_SEQUENCE;
	node->left = simple_command(cursor);
	if (!node->left)
		return (NULL);
	reset = *cursor;
	if (!*cursor || eat_token(cursor, TOKEN_SEMICOLON, reset))
		return (node);
	if (last_pipe(cursor))
		node->right = simple_command(cursor);
	else
		node->right = ast_pipe_sequence(cursor);
	if (*cursor && (*cursor)->type == TOKEN_SEMICOLON)
		*cursor = (*cursor)->next;
	return (node);
}
