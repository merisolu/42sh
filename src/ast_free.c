/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:58:11 by amann             #+#    #+#             */
/*   Updated: 2022/10/20 13:00:51 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

static void	tree_free_recursion(t_ast *root)
{
	if (root)
	{
		tree_free_recursion(root->right);
		ft_free_null_array((void **) root->arg_list);
		free(root->file);
		tree_free_recursion(root->left);
		free(root);
	}
	else
		return ;
}

void	ast_free(t_ast **tree_list)
{
	int	i;

	i = 0;
	while (tree_list[i])
	{
		tree_free_recursion(tree_list[i]);
		i++;
	}
	free(tree_list);
}
