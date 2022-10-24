/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:44:51 by amann             #+#    #+#             */
/*   Updated: 2022/10/24 15:16:18 by jumanner         ###   ########.fr       */
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

// static int	check_node_type(t_ast *node, t_ast_node_type type)
// {
// 	if (node && node->node_type == type)
// 		return (TRUE);
// 	return (FALSE);
// }

// /*
//  * TODO handle piping under (tree->right)..? maybe
//  * TODO check malloc protection in redirects works correctly.
//  */

// static int	get_args_from_tree(t_ast *tree, char ***args, t_redir *r)
// {
// 	t_ast	*cmd_node;

// 	if (!check_node_type(tree, AST_PIPE_SEQUENCE))
// 		return (0);
// 	if (tree->right)
// 		return (0);
// 	if (!tree->left || !check_node_type(tree->left, AST_SIMPLE_COMMAND))
// 		return (0);
// 	cmd_node = tree->left;
// 	if (cmd_node->right && (!handle_redirects(cmd_node->right, r)
// 		|| !check_node_type(cmd_node->right, AST_REDIRECTIONS)))
// 		return (0);
// 	if (!cmd_node->left || !check_node_type(cmd_node->left, AST_COMMAND_ARGS))
// 		return (0);
// 	*args = cmd_node->left->arg_list;
// 	return (1);
// }

static void	set_redir_struct(t_redir *r)
{
	r->fd_out = -1;
	r->fd_in = -1;
	r->saved_out = -1;
	r->saved_in = -1;
}

static void	connect_pipes(int read_pipe[2], int write_pipe[2])
{
	if (read_pipe[PIPE_READ] != -1)
	{
		if (dup2(read_pipe[PIPE_READ], STDIN_FILENO) == -1)
			print_error("read pipe dup2 fail", 1);
		close(read_pipe[PIPE_WRITE]);
		close(read_pipe[PIPE_READ]);
	}
	if (write_pipe[PIPE_READ] != -1)
	{
		if (dup2(write_pipe[PIPE_WRITE], STDOUT_FILENO) == -1)
			print_error("write pipe dup2 fail", 1);
		close(write_pipe[PIPE_READ]);
		close(write_pipe[PIPE_WRITE]);
	}
}

static pid_t	run_command(char *path, char *const *args, char *const *env, t_pipes *pipes)
{
	pid_t	pid;

	ft_dprintf(STDERR_FILENO, "Pipes: [%i, %i], [%i, %i]\n", pipes->read[0], pipes->read[1], pipes->write[0], pipes->write[1]);
	if (pipes->read[0] != -1 && pipes->write[0] != -1)
		dup2(pipes->write[PIPE_READ], pipes->read[PIPE_WRITE]);
	pid = fork();
	if (pid == -1)
		return (print_error(ERR_CHILD_PROC_FAIL, -1));
	if (pid > 0)
		return (pid);
	connect_pipes(pipes->read, pipes->write);
	signal(SIGINT, SIG_DFL);
	if (execve(path, args, env) == -1)
		exit(print_error(ERR_CHILD_PROC_FAIL, 1));
	return (0);
}

static void	execute_simple_command(t_ast *node, t_state *state, t_pipes *pipes, int is_at_end)
{
	if (!is_at_end)
	{
		if (pipe(pipes->write) == -1)
			print_error("Failed to create pipe", 1);
	}
	else
	{
		pipes->write[PIPE_READ] = -1;
		pipes->write[PIPE_WRITE] = -1;
	}

	ft_printf("Running %s\n", node->left->arg_list[0]);
	run_command(node->left->arg_list[0], node->left->arg_list, state->env, pipes);

	close(pipes->read[PIPE_READ]);
	close(pipes->read[PIPE_WRITE]);

	pipes->read[PIPE_READ] = pipes->write[PIPE_READ];
	pipes->read[PIPE_WRITE] = pipes->write[PIPE_WRITE];
}

static int is_at_end_check(t_ast *node)
{
	return !node->right || node->right->node_type == AST_SIMPLE_COMMAND;
}

static void	execute_tree(t_ast *node, t_state *state, t_pipes *pipes, int is_at_end)
{
	if (node->node_type == AST_SIMPLE_COMMAND)
	{
		if (node->right)
			ft_printf("Redirects are not implemented yet. Not running anything.\n");
		else
			execute_simple_command(node, state, pipes, is_at_end);
		return ;
	}
	else if (node->node_type == AST_PIPE_SEQUENCE)
	{
		execute_tree(node->left, state, pipes, !node->right);
		if (node->right)
			execute_tree(node->right, state, pipes, is_at_end_check(node));
	}
}

// /bin/ls -l / | /usr/bin/grep A | /usr/bin/wc -l
static void	execute_tree_list(t_ast **tree_list, t_state *state)
{
	t_redir	r;
	t_pipes	pipes;
	char	**args;
	int		i;

	if (!tree_list)
		return ;
	set_redir_struct(&r);
	pipes.read[0] = -1;
	pipes.read[1] = -1;
	pipes.write[0] = -1;
	pipes.write[1] = -1;
	args = NULL;
	i = 0;
	while (tree_list[i] != NULL)
	{
		execute_tree(tree_list[i], state, &pipes, 0);
		i++;
	}

	close(pipes.read[PIPE_READ]);
	close(pipes.read[PIPE_WRITE]);

	print_ast(tree_list);
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
