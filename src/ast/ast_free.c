/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:58:11 by amann             #+#    #+#             */
/*   Updated: 2022/12/21 15:57:50 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	clear_redir_and_members(t_ast_redir *redir)
{
	ft_strdel(&(redir->redir_file));
	ft_strdel(&(redir->redir_op));
	ft_memdel((void **)&redir);
}

void	ast_free_redirs(t_ast **root)
{
	size_t	i;

	i = 0;
	while ((*root)->redirs[i])
	{
		clear_redir_and_members((*root)->redirs[i]);
		i++;
	}
	ft_memdel((void **)&((*root)->redirs));
	return ;
}

/*
 * Takes a pointer to a list of trees and iterates through them, from the
 * right-most node first, freeing any pointers to heap allocated memory.
 * Finally, the pointer to the list of trees is freed.
 *
 * Heap memory:
 * - the node itself
 * - **arg_list (array of strings)
 * - **redirs (array of structs)
 * - *file (in the redir structs)
 */

void	ast_free_recursion(t_ast *node)
{
	if (!node)
		return ;
	ast_free_recursion(node->left);
	ast_free_recursion(node->right);
	node->arg_list = ft_free_null_array((void **) node->arg_list);
	node->var_list = ft_free_null_array((void **) node->var_list);
	if (node->redirs)
		ast_free_redirs(&node);
	ft_memdel((void **)&node);
}

void	ast_free(t_ast ***ast_list)
{
	int	i;

	i = 0;
	while ((*ast_list)[i])
	{
		ast_free_recursion((*ast_list)[i]);
		(*ast_list)[i] = NULL;
		i++;
	}
	free(*ast_list);
	*ast_list = NULL;
}
