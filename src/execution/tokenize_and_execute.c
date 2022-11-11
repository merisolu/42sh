/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:44:51 by amann             #+#    #+#             */
/*   Updated: 2022/11/11 15:36:57 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_at_end_check(t_ast *node)
{
	return (!node->right || node->right->node_type == AST_SIMPLE_COMMAND);
}

static pid_t	execute_simple_command(t_ast_execution *ctx, t_state *state)
{
	pid_t	result;

	result = -1;
	if (!ctx->is_at_end)
	{
		if (pipe(ctx->pipes->write) == -1)
			print_error(ERR_PIPE_FAIL, 1);
	}
	else if (ctx->node->right
		&& ft_strequ(ctx->node->right->in_type, REDIR_HEREDOC))
	{
		if (pipe(ctx->pipes->read) == -1)
			print_error(ERR_PIPE_FAIL, 1);
	}
	else
		pipe_reset(ctx->pipes->write);
	if (ctx->node->left && ctx->node->left->arg_list)
	{
		result = execute(
				ctx->node->left->arg_list, state, ctx);
	}
	pipe_close(ctx->pipes->read);
	pipes_copy(ctx->pipes->read, ctx->pipes->write);
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
	int		ret;
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
		if (tree_pid != -1 && waitpid(tree_pid, &ret, 0) != -1)
			set_return_value(get_return_value_from_status(ret), state);
		i++;
	}
	pipe_close(pipes.read);
	ast_free(tree_list);
	free(redir);
}

void	tokenize_and_execute(t_state *state)
{
	t_tokenizer	tokenizer;

	if (ft_strisempty(state->input_context.input))
	{
		ft_putchar('\n');
		clear_input(&(state->input_context));
		return ;
	}
	if (!terminal_apply_config(&(state->orig_conf)))
	{
		print_error(ERR_TERMIOS_FAIL, 1);
		return ;
	}
	history_store(state->input_context.input, state);
	state->input_context.cursor = ft_strlen(state->input_context.input);
	move_cursor_to_saved_position(&(state->input_context));
	ft_putchar('\n');
	execute_tree_list(construct_ast_list(
			tokenize(state->input_context.input, &tokenizer)), state);
	clear_input(&(state->input_context));
	if (!terminal_apply_config(&(state->input_conf)))
		print_error(ERR_TERMIOS_FAIL, 1);
}
