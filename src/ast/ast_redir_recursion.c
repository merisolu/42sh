/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir_recursion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:42:07 by amann             #+#    #+#             */
/*   Updated: 2022/10/27 11:35:16 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static int	add_redir_out(t_ast *node, t_token **cursor)
{
	if (node->out_type)
		ft_strdel(&(node->out_type));
	node->out_type = ft_strdup((*cursor)->value);
	if (!node->out_type)
		return (print_error(ERR_MALLOC_FAIL, 0));
	*cursor = (*cursor)->next;
	if (!(*cursor) || (*cursor)->type != TOKEN_WORD)
		return (print_error(ERR_SYNTAX, 0));
	if (node->out_file)
		ft_strdel(&(node->out_file));
	node->out_file = ft_strdup((*cursor)->value);
	if (!node->out_file)
		return (print_error(ERR_MALLOC_FAIL, 0));
	*cursor = (*cursor)->next;
	return (1);
}

static int	add_redir_in(t_ast *node, t_token **cursor)
{
	if (node->in_type)
		ft_strdel(&(node->in_type));
	node->in_type = ft_strdup((*cursor)->value);
	if (!node->in_type)
		return (print_error(ERR_MALLOC_FAIL, 0));
	*cursor = (*cursor)->next;
	if (!(*cursor) || (*cursor)->type != TOKEN_WORD)
		return (print_error(ERR_SYNTAX, 0));
	if (node->in_file)
		ft_strdel(&(node->in_file));
	node->in_file = ft_strdup((*cursor)->value);
	if (!node->in_file)
		return (print_error(ERR_MALLOC_FAIL, 0));
	*cursor = (*cursor)->next;
	return (1);
}

int	ast_redirect_recursion(t_ast *node, t_token **cursor)
{
	if (*cursor && (*cursor)->type == TOKEN_GT)
	{
		if (!add_redir_out(node, cursor))
			return (0);
	}
	if (*cursor && (*cursor)->type == TOKEN_LT)
	{
		if (!add_redir_in(node, cursor))
			return (0);
	}
	if (*cursor
		&& ((*cursor)->type == TOKEN_GT || (*cursor)->type == TOKEN_LT))
		ast_redirect_recursion(node, cursor);
	return (1);
}
