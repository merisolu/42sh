/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:55:17 by amann             #+#    #+#             */
/*   Updated: 2022/10/25 14:37:48 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	pipes_in_queue(t_token *cursor)
{
	if (cursor && cursor->type == TOKEN_PIPE)
		cursor = cursor->next;
	while (cursor)
	{
		if (cursor->type == TOKEN_PIPE)
			return (TRUE);
		cursor = cursor->next;
	}
	return (FALSE);
}

static int	add_redirects(t_token **cursor, t_ast **node)
{
	*node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!node)
		return (print_error(ERR_MALLOC_FAIL, 0));
	(*node)->node_type = AST_REDIRECTIONS;
	(*node)->token = *cursor;
	if (!ast_redirect_recursion(*node, cursor))
		return (0);
	return (1);
}

static t_ast	*create_cmd_args_node(t_token **cursor)
{
	t_ast	*res;

	res = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!res)
	{
		print_error(ERR_MALLOC_FAIL, 0);
		return (NULL);
	}
	res->node_type = AST_COMMAND_ARGS;
	res->token = *cursor;
	res->arg_list = ast_add_args(cursor);
	if (!(res->arg_list))
		return (NULL);
	return (res);
}

static t_ast	*simple_command(t_token **cursor)
{
	t_ast	*res;

	res = NULL;
	if (!*cursor || (*cursor)->type != TOKEN_WORD)
		return (NULL);
	res = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!res)
	{
		print_error(ERR_MALLOC_FAIL, 0);
		return (0);
	}
	res->node_type = AST_SIMPLE_COMMAND;
	res->left = create_cmd_args_node(cursor);
	if (*cursor && ((*cursor)->type == TOKEN_LT
			|| (*cursor)->type == TOKEN_GT))
	{
		if (!add_redirects(cursor, &(res->right)))
			return (NULL);
	}
	else
		res->right = NULL;
	return (res);
}

t_ast	*ast_pipe_sequence(t_token **cursor)
{
	t_ast	*new_node;

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
	if (*cursor && (*cursor)->type == TOKEN_SEMICOLON)
		return (new_node);
	if (!(*cursor))
		return (new_node);
	if ((*cursor)->type != TOKEN_WORD)
		*cursor = (*cursor)->next;
	if (*cursor && pipes_in_queue(*cursor))
		new_node->right = ast_pipe_sequence(cursor);
	else if (*cursor)
		new_node->right = simple_command(cursor);
	return (new_node);
}
