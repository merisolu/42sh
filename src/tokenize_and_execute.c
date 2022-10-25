/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:44:51 by amann             #+#    #+#             */
/*   Updated: 2022/10/25 14:00:22 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static pid_t	execute_simple_command(t_ast *node, t_state *state, t_pipes *pipes, int is_at_end)
{
	pid_t	result;

	if (!is_at_end)
	{
		if (pipe(pipes->write) == -1)
			print_error(ERR_PIPE_FAIL, 1);
	}
	else
		pipe_reset(pipes->write);
	result = execute(node->left->arg_list, &(state->env), pipes);
	pipe_close(pipes->read);
	pipes_copy(pipes->read, pipes->write);
	return (result);
}

static int is_at_end_check(t_ast *node)
{
	return !node->right || node->right->node_type == AST_SIMPLE_COMMAND;
}

static pid_t	execute_tree(t_ast *node, t_state *state, t_redir *redir, t_pipes *pipes, int is_at_end)
{
	pid_t	result;

	result = -1;
	if (node->node_type == AST_SIMPLE_COMMAND)
	{
		if (node->right)
			handle_redirects(node->right, redir);
		result = execute_simple_command(node, state, pipes, is_at_end);
		reset_io(*redir);
	}
	else if (node->node_type == AST_PIPE_SEQUENCE)
	{
		result = execute_tree(node->left, state, redir, pipes, !node->right);
		if (node->right)
			result = execute_tree(node->right, state, redir, pipes, is_at_end_check(node));
	}
	return (result);
}

// ls -l / | grep A | wc -l
static void	execute_tree_list(t_ast **tree_list, t_state *state)
{
	t_redir	redir;
	t_pipes	pipes;
	pid_t	tree_pid;
	char	**args;
	int		i;

	if (!tree_list)
		return ;
	initialize_redir_struct(&redir);
	pipes_reset(pipes.read, pipes.write);
	args = NULL;
	i = 0;
	while (tree_list[i] != NULL)
	{
		tree_pid = execute_tree(tree_list[i], state, &redir, &pipes, 0);
		if (tree_pid != -1)
			waitpid(tree_pid, NULL, 0);
		i++;
	}
	pipe_close(pipes.read);
	ast_free(tree_list);
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
