/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_simple_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:39:33 by amann             #+#    #+#             */
/*   Updated: 2022/11/15 17:40:06 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

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

int	ast_simple_command(t_token **cursor, t_ast **node)
{
	t_token	*reset;

	reset = *cursor;
	*node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!node)
		return (print_error(ERR_MALLOC_FAIL, 0));
	(*node)->node_type = AST_SIMPLE_COMMAND;
	while (cursor && *cursor)
	{
		if (!*cursor || read_token(cursor, TOKEN_SEMICOLON, reset)
			|| read_token(cursor, TOKEN_PIPE, reset))
			break ;
		if (!args_node(cursor, &((*node)->left))
			|| !redirects_node(cursor, &((*node)->right)))
			return (0);
		reset = *cursor;
	}
	return (1);
}
