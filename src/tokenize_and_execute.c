/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:44:51 by amann             #+#    #+#             */
/*   Updated: 2022/10/25 10:51:42 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

	// ft_dprintf(STDERR_FILENO, "Pipes: [%i, %i], [%i, %i]\n", pipes->read[0], pipes->read[1], pipes->write[0], pipes->write[1]);
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

static pid_t	execute_simple_command(t_ast *node, t_state *state, t_pipes *pipes, int is_at_end)
{
	pid_t	result;

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

	result = run_command(node->left->arg_list[0], node->left->arg_list, state->env, pipes);

	close(pipes->read[PIPE_READ]);
	close(pipes->read[PIPE_WRITE]);

	pipes->read[PIPE_READ] = pipes->write[PIPE_READ];
	pipes->read[PIPE_WRITE] = pipes->write[PIPE_WRITE];

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

// /bin/ls -l / | /usr/bin/grep A | /usr/bin/wc -l
static void	execute_tree_list(t_ast **tree_list, t_state *state)
{
	t_redir	redir;
	t_pipes	pipes;
	char	**args;
	int		i;

	if (!tree_list)
		return ;
	set_redir_struct(&redir);
	pipes.read[0] = -1;
	pipes.read[1] = -1;
	pipes.write[0] = -1;
	pipes.write[1] = -1;
	args = NULL;
	i = 0;
	while (tree_list[i] != NULL)
	{
		waitpid(execute_tree(tree_list[i], state, &redir, &pipes, 0), NULL, 0);
		i++;
	}

	close(pipes.read[PIPE_READ]);
	close(pipes.read[PIPE_WRITE]);

	// print_ast(tree_list);
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
