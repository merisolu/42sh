/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:44:51 by amann             #+#    #+#             */
/*   Updated: 2022/11/03 13:10:09 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_at_end_check(t_ast *node)
{
	return (!node->right || node->right->node_type == AST_SIMPLE_COMMAND);
}

static pid_t	execute_simple_command(t_ast_execution *context, t_state *state)
{
	pid_t	result;

	result = -1;
	if (!context->is_at_end)
	{
		if (pipe(context->pipes->write) == -1)
			print_error(ERR_PIPE_FAIL, 1);
	}
	else
		pipe_reset(context->pipes->write);
	if (context->node->left && context->node->left->arg_list)
	{
		result = execute(
				context->node->left->arg_list, state, context);
	}
	pipe_close(context->pipes->read);
	pipes_copy(context->pipes->read, context->pipes->write);
	return (result);
}

static pid_t	execute_tree(t_ast_execution *ctx, t_state *state)
{
	pid_t			result;

	result = -1;
	if (ctx->node->node_type == AST_SIMPLE_COMMAND)
	{
		result = execute_simple_command(ctx, state);
		if (ctx->node->right)
			reset_io(ctx->redirect);
	}
	else if (ctx->node->node_type == AST_PIPE_SEQUENCE)
	{
		result = execute_tree(
				&(t_ast_execution){
				ctx->node->left, ctx->redirect, ctx->pipes, !ctx->node->right
			}, state);
		if (ctx->node->right)
			result = execute_tree(
					&(t_ast_execution){ctx->node->right, ctx->redirect,
					ctx->pipes, is_at_end_check(ctx->node)}, state);
	}
	return (result);
}

static void	execute_tree_list(t_ast **tree_list, t_state *state)
{
	t_redir	*redir;
	t_pipes	pipes;
	pid_t	tree_pid;
	int		i;

	if (!tree_list)
		return ;
	redir = (t_redir *) ft_memalloc(sizeof(t_redir));
	pipes_reset(pipes.read, pipes.write);
	i = 0;
	while (tree_list[i] != NULL)
	{
		initialize_redir_struct(redir);
		ast_parse_expansions(tree_list[i], state);
		tree_pid = execute_tree(
				&(t_ast_execution){tree_list[i], redir, &pipes, 0}, state);
		if (tree_pid != -1)
			waitpid(tree_pid, NULL, 0);
		i++;
	}
	pipe_close(pipes.read);
	ast_free(tree_list);
	free(redir);
}

void	tokenize_and_execute(t_state *state)
{
	if (ft_strisempty(state->input_context.input))
	{
		clear_input(&(state->input_context), 1);
		return ;
	}
	if (!set_orig_config(state))
	{
		print_error(ERR_TERMIOS_FAIL, 1);
		return ;
	}
	history_store(state->input_context.input, state);
	state->input_context.cursor = ft_strlen(state->input_context.input);
	move_cursor_to_saved_position(&(state->input_context));
	ft_putchar('\n');
	execute_tree_list(construct_ast_list(tokenize(state)), state);
	clear_input(&(state->input_context), 0);
	if (!set_input_config(state))
		print_error(ERR_TERMIOS_FAIL, 1);
}
