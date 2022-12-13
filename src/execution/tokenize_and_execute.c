/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:44:51 by amann             #+#    #+#             */
/*   Updated: 2022/12/13 12:54:52 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_at_end_check(t_ast *node)
{
	return (!node->right || node->right->node_type == AST_SIMPLE_COMMAND);
}

static pid_t	execute_simple_command(t_ast_context *ctx, t_state *state)
{
	pid_t	result;

	result = -1;
	if (!ctx->is_at_end && pipe(ctx->pipes->write) == -1)
		return (print_error(-1, ERRTEMPLATE_SIMPLE, ERR_PIPE_FAIL));
	if (ctx->node->right && !heredoc_run(ctx->node->right, ctx->pipes))
		return (print_error(-1, ERRTEMPLATE_SIMPLE, ERR_HEREDOC_FAIL));
	if (ctx->is_at_end)
		pipe_reset(ctx->pipes->write);
	if (ctx->node->left && ctx->node->left->arg_list
		&& ctx->node->left->arg_list[0])
	{
		result = execute(ctx->node->left->arg_list, state, ctx);
		if (!env_set("_", ctx->node->left->arg_list[ft_null_array_len((void **)
						ctx->node->left->arg_list) - 1], &(state->env)))
			return (-1);
	}
	else if (ctx->node->left && ctx->node->right)
	{
		result = 0;
		handle_redirects(ctx->node->right, ctx->redirect);
	}
	pipe_close(ctx->pipes->read);
	pipes_copy(ctx->pipes->read, ctx->pipes->write);
	return (result);
}

static bool	execute_ast(t_ast_context *ctx, t_state *state)
{
	bool	result;
	pid_t	pid;

	result = false;
	if (ctx->node->node_type == AST_SIMPLE_COMMAND)
	{
		pid = execute_simple_command(ctx, state);
		if (ctx->node->right)
			reset_io(ctx->redirect);
		if (pid == -1 || !pids_add(pid, state))
			return (false);
		return (true);
	}
	else if (ctx->node->node_type == AST_PIPE_SEQUENCE)
	{
		result = execute_ast(&(t_ast_context){ctx->node->left, ctx->redirect,
				ctx->pipes, !ctx->node->right}, state);
		if (result && ctx->node->right)
			result = execute_ast(
					&(t_ast_context){ctx->node->right, ctx->redirect,
					ctx->pipes, is_at_end_check(ctx->node)}, state);
	}
	return (result);
}

static void	execute_ast_list(t_ast **ast, t_state *state)
{
	t_redir	*redir;
	t_pipes	pipes;
	int		i;
	bool	res;

	if (!ast)
		return ;
	check_print_ast(ast, state, false);
	redir = (t_redir *) ft_memalloc(sizeof(t_redir));
	pipes_reset(pipes.read, pipes.write);
	i = 0;
	while (ast[i] != NULL)
	{
		initialize_redir_struct(redir);
		parse_expansions(ast[i], state);
		res = execute_ast(&(t_ast_context){ast[i], redir, &pipes, 0}, state);
		set_return_value(pids_wait(state), state);
		if (!res)
			break ;
		handle_logical_ops(ast, state, &i);
	}
	pipe_close(pipes.read);
	check_print_ast(ast, state, true);
	ast_free(&ast);
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
		print_error(1, ERRTEMPLATE_SIMPLE, ERR_TERMIOS_FAIL);
		return ;
	}
	state->input_context.cursor = ft_strlen(state->input_context.input);
	move_cursor_to_saved_position(&(state->input_context));
	ft_putchar('\n');
	execute_ast_list(construct_ast_list(
			tokenize(state->input_context.input, &tokenizer)), state);
	history_store(state->input_context.input, state, 0);
	clear_input(&(state->input_context));
	if (!terminal_apply_config(&(state->input_conf)))
		print_error(1, ERRTEMPLATE_SIMPLE, ERR_TERMIOS_FAIL);
}
