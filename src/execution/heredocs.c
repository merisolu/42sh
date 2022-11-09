/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:56:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/09 11:24:19 by jumanner         ###   ########.fr       */
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

// TODO: Check get_line error
int	heredoc_run(t_ast *redir_node, t_pipes *pipes)
{
	t_input_context	ctx;
	struct termios	original;
	char			*mark;

	if (!ft_strequ(redir_node->in_type, REDIR_HEREDOC))
		return (1);
	if (!heredoc_setup(&ctx, redir_node->in_file, &mark, &original))
		return (0);
	while (get_line(&ctx) != INPUT_MARK_FOUND)
		display(&ctx);
	ft_putchar('\n');
	if (!terminal_apply_config(&original))
	{
		heredoc_cleanup(&ctx, &original, mark);
		return (print_error(ERR_TERMIOS_FAIL, 0));
	}
	ctx.input[ft_strlen(ctx.input) - (ft_strlen(ctx.mark) - 1)] = '\0';
	ft_putstr_fd(ctx.input, pipes->read[PIPE_WRITE]);
	heredoc_cleanup(&ctx, &original, mark);
	return (1);
}
