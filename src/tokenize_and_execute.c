/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:44:51 by amann             #+#    #+#             */
/*   Updated: 2022/10/20 16:26:24 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
//maybe put this in a header file
#include <fcntl.h>


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

//TODO error handling - at present we don't reset STDIN and STDOUT properly
//TODO > should remove any contents of the file before writing onto it.

int	handle_redirects(t_ast *redir_node, t_redir *r)
{
	char		*file;
	static int	o_flags;
	static int	permissions;

	o_flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (ft_strequ(redir_node->token->value, ">>"))
		o_flags = O_WRONLY | O_CREAT | O_APPEND;
	permissions = S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR | S_IROTH;
	file = redir_node->file;
	if (!file || !redir_node->token->value)
		return (print_error("bad filename (paceholder)\n", 0));
	r->fd_out = open(file, o_flags, permissions);
	if (r->fd_out == -1)
		return (print_error("could not open! (paceholder)\n", 0));
	r->saved_out = dup(STDOUT_FILENO);
	if (r->saved_out == -1)
		return (print_error("could not dup! (paceholder)\n", 0));
	if (dup2(r->fd_out, STDOUT_FILENO) == -1)
		return (print_error("could not dup2! (paceholder)\n", 0));
	close(r->fd_out);
	return (1);
}

/*
 * TODO handle piping under (tree->right)
 * TODO handle redirects under (cmd_node->right)
 */

static int	get_args_from_tree(t_ast *tree, char ***args, t_redir *r)
{
	t_ast	*cmd_node;

	if (!check_node_type(tree, AST_PIPE_SEQUENCE))
		return (0);
	if (tree->right)
		return (0);
	if (!tree->left || !check_node_type(tree->left, AST_SIMPLE_COMMAND))
		return (0);
	cmd_node = tree->left;
	if (cmd_node->right && (!handle_redirects(cmd_node->right, r)
		|| !check_node_type(cmd_node->right, AST_REDIRECTIONS)))
		return (-1);
	if (!cmd_node->left || !check_node_type(cmd_node->left, AST_COMMAND_ARGS))
		return (0);
	*args = cmd_node->left->arg_list;
	return (1);
}

static void	execute_tree_list(t_ast **tree_list, t_state *state)
{
	t_redir	r;
	char	**args;
	int		i;

	r.fd_out = -1;
	r.fd_in = -1;
	r.saved_out = -1;
	r.saved_in = -1;
	if (tree_list)
	{
		args = NULL;
		i = 0;
		while (get_args_from_tree(tree_list[i], &args, &r))
		{
			set_return_value(execute(args, state), state);
			if (args)
				env_set(
					"_",
					args[ft_null_array_len((void **)args) - 1],
					&(state->env)
					);
			if (r.saved_out != -1)
			{
				if (dup2(r.saved_out, STDOUT_FILENO) == -1)
				{
					ft_dprintf(STDERR_FILENO, "could not dup2! (paceholder)\n");
					return ;
				}
				r.saved_out = -1;
			}
			i++;
		}
		//print_ast(tree_list);
		ast_free(tree_list);
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
	ft_putchar('\n');
	execute_tree_list(parse(tokenize(state->input), state), state);
	clear_input(state, 0);
	if (!set_input_config(state))
		print_error(ERR_TERMIOS_FAIL, 1);
}
