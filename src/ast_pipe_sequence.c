/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe_sequence.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:55:17 by amann             #+#    #+#             */
/*   Updated: 2022/11/01 13:49:34 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	last_pipe(t_token **cursor)
{
	t_token *reset;
	t_token	*check;

	reset = *cursor;
	eat_token(cursor, TOKEN_PIPE, reset);
	check = *cursor;
	print_tokens(*cursor);
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
	return (ast_redirect_recursion(*node, cursor));
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
	{
		print_error(ERR_MALLOC_FAIL, 0);
		return (NULL);
	}
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
		return (NULL);
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
	return (node);
}
/*
if (*cursor && ((*cursor)->type == TOKEN_LT || (*cursor)->type == TOKEN_GT
				|| ast_fd_agg_format_check(cursor)))
		{
			if (!add_redirects(cursor, &(node->right)))
			{
				return (NULL);
			}
		}
*/
/*
t_ast	*ast_pipe_sequence(t_token **cursor)
{
	t_ast	*new_node;

	print_tokens(*cursor);
	new_node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!new_node)
	{
		print_error(ERR_MALLOC_FAIL, 0);
		return (NULL);
	}
	new_node->node_type = AST_PIPE_SEQUENCE;
	new_node->left = simple_command(cursor);
	if (!(new_node->left))
		return (NULL);
	if (!(*cursor) || (*cursor && (*cursor)->type == TOKEN_SEMICOLON))
	{
		ft_putendl("here");
		return (new_node);
	}
	if ((*cursor)->type != TOKEN_WORD)
		*cursor = (*cursor)->next;
	if (*cursor && pipes_in_queue(*cursor))
		new_node->right = ast_pipe_sequence(cursor);
	else if (*cursor)
		new_node->right = simple_command(cursor);
	return (new_node);
}*/
