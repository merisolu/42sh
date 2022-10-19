/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:55:17 by amann             #+#    #+#             */
/*   Updated: 2022/10/19 13:40:15 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	pipes_in_queue(t_token *cursor)
{
	if (cursor->type == TOKEN_PIPE)
		cursor = cursor->next;
	while (cursor)
	{
		if (cursor->type == TOKEN_PIPE)
			return (TRUE);
		cursor = cursor->next;
	}
	return (FALSE);
}

static int	check_token_type(t_token **cursor, enum e_token_type type)
{
	if (*cursor && (*cursor)->type == type)
		return (TRUE);
	return (FALSE);
}

static t_ast	*add_redirects(t_token **cursor)
{
	t_ast	*node;

	node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->node_type = AST_REDIRECTIONS;
	node->token = *cursor;
	*cursor = (*cursor)->next;
	if (check_token_type(cursor, TOKEN_WORD))
		node->file = ft_strdup((*cursor)->value);
	*cursor = (*cursor)->next;
	return (node);
}

/*
 * TODO multiple redirections in the same command...?
 */

static t_ast	*simple_command(t_token **cursor)
{
	t_ast	*res;

	res = NULL;
	if (check_token_type(cursor, TOKEN_WORD))
	{
		res = (t_ast *) ft_memalloc(sizeof(t_ast));
		if (!res)
			return (NULL);
		res->node_type = AST_SIMPLE_COMMAND;
		res->left = (t_ast *) ft_memalloc(sizeof(t_ast));
		if (!res->left)
		{
			free(res);
			return (NULL);
		}
		res->left->node_type = AST_COMMAND_ARGS;
		res->left->token = *cursor;
		res->left->arg_list = ast_add_args(cursor);
		if (check_token_type(cursor, TOKEN_LT)
			|| check_token_type(cursor, TOKEN_GT))
			res->right = add_redirects(cursor);
		else
			res->right = NULL;
	}
	return (res);
}

t_ast	*ast_pipe_sequence(t_token **cursor)
{
	t_ast	*new_node;

	new_node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->node_type = AST_PIPE_SEQUENCE;
	new_node->left = simple_command(cursor);
	if (!(new_node->left))
		return (NULL);
	if (*cursor && check_token_type(cursor, TOKEN_SEMICOLON))
		return (new_node);
	if (!(*cursor))
		return (new_node);
	if (!check_token_type(cursor, TOKEN_WORD))
		*cursor = (*cursor)->next;
	if (*cursor && pipes_in_queue(*cursor))
		new_node->right = ast_pipe_sequence(cursor);
	else if (*cursor)
	{
		new_node->right = simple_command(cursor);
	}
	return (new_node);
}
