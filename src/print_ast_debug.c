/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:07:12 by amann             #+#    #+#             */
/*   Updated: 2022/10/13 15:08:17 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	print_ast_node(t_ast *node, int space, int count)
{
	ft_putchar('\n');
	for (int i = count; i < space; i++)
		ft_putchar(' ');
	if (node->node_type == AST_PIPE_SEQUENCE)
		ft_putendl("PIPE_SEQUENCE");
	else if (node->node_type == AST_SIMPLE_COMMAND)
		ft_putendl("SIMPLE_COMMAND");
	if (node->node_type == AST_COMMAND_ARGS)
	{
		for (int i = 0; (node->arg_list)[i]; i++)
			ft_printf("%s ", (char *)(node->arg_list)[i]);
		ft_putchar('\n');
	}
}

static void	tree_iterate(t_ast *root, int space)
{
	int count;

	count = 20;
	if (root)
	{
		space += count;
		tree_iterate(root->right, space);
		print_ast_node(root, space, count);
		tree_iterate(root->left, space);
	}
	else
		return ;
}

void	print_ast(t_ast **tree)
{
	size_t	idx;
	t_ast	*root;

	ft_putendl("########## AST ##########");
	if (!tree || !(tree[0]))
	{
		ft_putendl("something terrible happened");
		return ;
	}
	idx = 0;
	while (tree[idx])
	{
		root = tree[idx];
		tree_iterate(root, 0);
		ft_printf("The above is tree number %zu\n", idx + 1);
		idx++;
	}
}
