/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:56:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/10 12:01:10 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	*construct_mark(char *base)
{
	char	*result;

	result = ft_strnew(ft_strlen(base) + 2);
	ft_strcpy(result + 1, base);
	result[0] = '\n';
	result[ft_strlen(base) + 1] = '\n';
	return (result);
}

static void	heredoc_cleanup(t_input_context *ctx, struct termios *original, \
char *mark)
{
	free(mark);
	input_context_free(ctx);
	if (!terminal_apply_config(original))
		print_error(ERR_INPUT_CONTEXT_FAIL, 0);
}

static int	heredoc_setup(t_input_context *ctx, char *base_mark, char **mark, \
struct termios *original)
{
	struct termios	input;

	if (!terminal_get_configs(&input, original))
		return (0);
	*mark = construct_mark(base_mark);
	if (!*mark)
		return (print_error(ERR_MALLOC_FAIL, 0));
	if (!input_context_set(ctx,
			MULTILINE_PROMPT, MULTILINE_PROMPT, *mark))
	{
		heredoc_cleanup(ctx, original, *mark);
		return (print_error(ERR_INPUT_CONTEXT_FAIL, 0));
	}
	if (!terminal_apply_config(&input))
	{
		heredoc_cleanup(ctx, original, *mark);
		return (print_error(ERR_TERMIOS_FAIL, 0));
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
		ctx->input[ft_strlen(ctx->input) - (ft_strlen(ctx->mark) - 1)] = '\0';
	}
}

int	heredoc_run(t_ast *redir_node, t_pipes *pipes)
{
	t_input_context	ctx;
	struct termios	original;
	char			*mark;

	if (!ft_strequ(redir_node->in_type, REDIR_HEREDOC))
		return (1);
	if (!heredoc_setup(&ctx, redir_node->in_file, &mark, &original))
		return (0);
	display(&ctx);
	input_loop(&ctx);
	if (!terminal_apply_config(&original))
	{
		heredoc_cleanup(&ctx, &original, mark);
		return (print_error(ERR_TERMIOS_FAIL, 0));
	}
	ft_putstr_fd(ctx.input, pipes->read[PIPE_WRITE]);
	heredoc_cleanup(&ctx, &original, mark);
	return (1);
}
