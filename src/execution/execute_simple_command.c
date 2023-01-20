/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:15:30 by amann             #+#    #+#             */
/*   Updated: 2023/01/17 16:58:44 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	handle_vars(t_ast_context *ctx, t_state *state)
{
	if (!ctx->node->left->arg_list[0] && ctx->node->left->var_list)
	{
		if (!set_internal_variables(ctx->node->left->var_list, state))
			return (-1);
		check_path_change(ctx->node->left->var_list, state, 1, false);
	}
	else if (ctx->node->left->arg_list[0] && ctx->node->left->var_list)
	{
		if (!remove_temp_vars_from_env(ctx, state))
			return (-1);
	}
	return (0);
}

static int	execute_sc_helper(t_ast_context *ctx, t_state *state, pid_t *result)
{
	if (ctx->node->left && ctx->node->left->arg_list
		&& ctx->node->left->arg_list[0])
	{
		*result = execute(ctx->node->left->arg_list, state, ctx);
		if (!env_set("_", ctx->node->left->arg_list[ft_null_array_len((void **)
						ctx->node->left->arg_list) - 1], &(state->env)))
			return (-1);
	}
	else if (ctx->node->left && ctx->node->right)
	{
		*result = 0;
		handle_redirects(ctx->node->right, ctx->redirect);
	}
	if (handle_vars(ctx, state) == -1)
		return (-1);
	return (0);
}

pid_t	execute_simple_command(t_ast_context *ctx, t_state *state)
{
	pid_t	result;

	result = -1;
	if (!ctx->is_at_end && pipe(ctx->pipes->write) == -1)
		return (print_error(-1, ERRTEMPLATE_SIMPLE, ERR_PIPE_FAIL));
	if (ctx->node->right && !heredoc_run(ctx->node->right, ctx->pipes))
		return (-1);
	if (ctx->is_at_end)
		pipe_reset(ctx->pipes->write);
	if (execute_sc_helper(ctx, state, &result) == -1)
		return (-1);
	pipe_close(ctx->pipes->read);
	pipes_copy(ctx->pipes->read, ctx->pipes->write);
	return (result);
}
