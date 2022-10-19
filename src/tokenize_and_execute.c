/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:44:51 by amann             #+#    #+#             */
/*   Updated: 2022/10/19 13:56:56 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 * check start == pipe_sequence node
 * check if right node is null (if not, we need to pipe something...)
 * check if left node contains a simple command (if not... bad things... exit)
 * move to command node.
 * check if right node is null (if not, we have to handle a redirection)
 * check if left node is command_args node
 * return a pointer to the arg_list from that node to the args variable
 *
 */

static int	check_node_type(t_ast *node, t_ast_node_type type)
{
	if (node && node->node_type == type)
		return (TRUE);
	return (FALSE);
}

/*
 * TODO handle piping under (tree->right)
 * TODO handle redirects under (cmd_node->right)
 */

static int	get_args_from_tree(t_ast *tree, char ***args)
{
	t_ast	*cmd_node;

	if (!check_node_type(tree, AST_PIPE_SEQUENCE))
		return (0);
	if (tree->right)
		return (0);
	if (!tree->left || !check_node_type(tree->left, AST_SIMPLE_COMMAND))
		return (0);
	cmd_node = tree->left;
	if (cmd_node->right)
		return (0);
	if (!cmd_node->left || !check_node_type(cmd_node->left, AST_COMMAND_ARGS))
		return (0);
	*args = cmd_node->left->arg_list;
	return (1);
}

static void	execute_tree_list(t_ast **tree_list, t_state *state)
{
	char	**args;
	int		i;

	if (tree_list)
	{
		args = NULL;
		i = 0;
		while (get_args_from_tree(tree_list[i], &args))
		{
			set_return_value(execute(args, state), state);
			if (args)
				env_set(
					"_",
					args[ft_null_array_len((void **)args) - 1],
					&(state->env)
					);
			i++;
		}
	}
}

/*
 * TODO We will also need our tree-freeing function here
 */

void	tokenize_and_execute(t_state *state)
{
	if (ft_strisempty(state->input))
	{
		clear_input(state, 1);
		return ;
	}
	if (!set_orig_config(state))
	{
		print_error(ERR_TERMIOS_FAIL, 1);
		return ;
	}
	history_store(state->input, state);
	state->cursor = ft_strlen(state->input);
	state->previous_input_length = 0;
	ft_putchar('\n');
	execute_tree_list(parse(tokenize(state->input), state), state);
	clear_input(state, 0);
	if (!set_input_config(state))
		print_error(ERR_TERMIOS_FAIL, 1);
}
