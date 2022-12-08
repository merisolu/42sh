/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:58:11 by amann             #+#    #+#             */
/*   Updated: 2022/12/08 14:26:13 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	ast_free_redirs(t_ast **root)
{
	size_t	i;

	i = 0;
	while ((*root)->redirs[i])
	{
		ft_strdel(&((*root)->redirs[i]->in_file));
		ft_strdel(&((*root)->redirs[i]->out_file));
		ft_strdel(&((*root)->redirs[i]->in_type));
		ft_strdel(&((*root)->redirs[i]->out_type));
		ft_memdel((void **)&(*root)->redirs[i]);
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
 *
 *
 */

void	ast_free_recursion(t_ast *root)
{
	if (!root)
		return ;
	ast_free_recursion(root->left);
	ast_free_recursion(root->right);
	root->arg_list = ft_free_null_array((void **) root->arg_list);
	if (root->redirs)
		ast_free_redirs(&root);
	ft_memdel((void **)&root);
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
