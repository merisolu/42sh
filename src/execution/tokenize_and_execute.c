/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:44:51 by amann             #+#    #+#             */
/*   Updated: 2023/01/23 11:39:58 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	cleanup_ast_list(t_ast **ast, t_redir **redir, t_pipes *pipes, \
t_state *state)
{
	free(redir);
	pipe_close(pipes->read);
	check_print_ast(ast, state, true);
	ast_free(&ast);
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
		if (pid == -1 || !pids_add(pid, ctx->job))
			return (false);
		return (true);
	}
	else if (ctx->node->node_type == AST_PIPE_SEQUENCE)
	{
		result = execute_ast(&(t_ast_context){ctx->node->left, ctx->redirect, \
			ctx->pipes, ctx->background, ctx->job, !ctx->node->right}, state);
		if (result && ctx->node->right)
			result = execute_ast(
					&(t_ast_context){ctx->node->right, ctx->redirect,
					ctx->pipes, ctx->background, ctx->job, (!ctx->node->right
						|| ctx->node->right->node_type == AST_SIMPLE_COMMAND)},
					state);
	}
	return (result);
}

static bool	setup_ast_list_execution(t_ast **ast, t_redir ***redir, \
t_pipes *pipes, t_state *state)
{
	check_print_ast(ast, state, false);
	*redir = (t_redir **)ft_memalloc(sizeof(t_redir *) * (INPUT_MAX_SIZE / 2));
	if (!redir)
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	pipes_reset(pipes->read, pipes->write);
	return (true);
}

static void	execute_ast_list(t_ast **ast, t_state *state)
{
	t_redir	**redir;
	t_pipes	pipes;
	int		i;
	t_job	*job;

	setup_ast_list_execution(ast, &redir, &pipes, state);
	i = 0;
	while (ast[i] != NULL && redir)
	{
		job = jobs_create(state);
		if (!job || !parse_expansions(ast[i], state)
			|| !execute_ast(&(t_ast_context){ast[i], redir, &pipes, \
			ast[i]->amp, job, 0}, state))
			break ;
		job->needs_status_print = ast[i]->amp;
		if (!ast[i]->amp)
		{
			job_wait(job, false, state);
			ioctl(STDIN_FILENO, TIOCSPGRP, &(state->group_id));
		}
		else
			job->state = JOB_RUNNING;
		handle_logical_ops(ast, state, &i);
	}
	cleanup_ast_list(ast, redir, &pipes, state);
}

void	tokenize_and_execute(t_state *state)
{
	t_tokenizer	tokenizer;
	t_ast		**ast_list;

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
	ast_list = construct_ast_list(
			tokenize(state->input_context.input, &tokenizer));
	if (ast_list)
		execute_ast_list(ast_list, state);
	history_store(state->input_context.input, state, 0);
	clear_input(&(state->input_context));
	if (!terminal_apply_config(&(state->input_conf)))
		print_error(1, ERRTEMPLATE_SIMPLE, ERR_TERMIOS_FAIL);
}
