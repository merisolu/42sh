/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:56:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/14 14:42:36 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	heredoc_cleanup(t_input_context *ctx, struct termios *original)
{
	input_context_free(ctx);
	if (!terminal_apply_config(original))
		print_error(0, ETEMPLATE_SHELL_SIMPLE, ERR_INPUT_CONTEXT_FAIL);
}

static int	heredoc_setup(t_input_context *ctx, char *mark, \
struct termios *original)
{
	struct termios	input;

	if (!terminal_get_configs(&input, original))
		return (0);
	if (!input_context_set(ctx,
			&(t_input_initializer){
			MULTILINE_PROMPT, MULTILINE_PROMPT, mark, NULL}))
	{
		heredoc_cleanup(ctx, original);
		return (print_error(
				0, ETEMPLATE_SHELL_SIMPLE, ERR_INPUT_CONTEXT_FAIL));
	}
	if (!terminal_apply_config(&input))
	{
		heredoc_cleanup(ctx, original);
		return (print_error(0, ETEMPLATE_SHELL_SIMPLE, ERR_TERMIOS_FAIL));
	}
	save_cursor(ctx);
	return (1);
}

static void	input_loop(t_input_context *ctx)
{
	t_input_result	input_result;

	input_result = get_input(ctx);
	while (input_result != INPUT_MARK_FOUND
		&& input_result != INPUT_CALLED_FOR_EXIT)
		input_result = get_input(ctx);
	if (input_result == INPUT_MARK_FOUND)
	{
		ft_putchar('\n');
		ctx->input[ft_strlen(ctx->input) - ft_strlen(ctx->mark)] = '\0';
	}
}

static t_ast_redir	*find_heredoc_node(t_ast *node)
{
	t_ast_redir	*res;
	size_t		i;

	if (!node->redirs || !node->redirs[0])
		return (NULL);
	res = NULL;
	i = 0;
	while (node->redirs[i])
	{
		if (ft_strequ(node->redirs[i]->redir_op, REDIR_HEREDOC))
			res = node->redirs[i];
		i++;
	}
	return (res);
}

int	heredoc_run(t_ast *redir_node, t_pipes *pipes)
{
	t_input_context	ctx;
	struct termios	original;
	t_ast_redir		*heredoc_node;

	heredoc_node = find_heredoc_node(redir_node);
	if (!heredoc_node)
		return (1);
	if (!ft_strequ(heredoc_node->redir_op, REDIR_HEREDOC))
		return (1);
	if (pipe(pipes->read) == -1)
		return (0);
	if (!heredoc_setup(&ctx, heredoc_node->redir_file, &original))
		return (0);
	display(&ctx, 0);
	input_loop(&ctx);
	if (!terminal_apply_config(&original))
	{
		heredoc_cleanup(&ctx, &original);
		return (print_error(0, ETEMPLATE_SHELL_SIMPLE, ERR_TERMIOS_FAIL));
	}
	ft_putstr_fd(ctx.input, pipes->read[PIPE_WRITE]);
	heredoc_cleanup(&ctx, &original);
	return (1);
}
