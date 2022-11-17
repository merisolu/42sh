/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:58:11 by amann             #+#    #+#             */
/*   Updated: 2022/11/17 15:51:58 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
 * Takes a pointer to a list of trees and iterates through them, from the
 * right-most node first, freeing any pointers to heap allocated memory.
 * Finally, the pointer to the list of trees is freed.
 *
 * Heap memory:
 * - the node itself
 * - **arg_list (array of strings)
 * - *file (if a redirection node)
 *
 */

void	ast_free_recursion(t_ast *root)
{
	if (!root)
		return ;
	ast_free_recursion(root->left);
	ast_free_recursion(root->right);
	ft_free_null_array((void **) root->arg_list);
//	free(root->in_file);
//	free(root->out_file);
//	free(root->in_type);
//	free(root->out_type);
	free(root);
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
