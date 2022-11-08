/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:56:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/08 14:22:08 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	heredoc_cleanup(t_input_context *context, struct termios *original)
{
	input_context_free(context);
	terminal_apply_config(original);
}

static int	heredoc_setup(t_input_context *context, char *mark, \
struct termios *original)
{
	struct termios	input;

	if (!terminal_get_configs(&input, original))
		return (0);
	if (!input_context_set(context,
			MULTILINE_PROMPT, MULTILINE_PROMPT, mark))
	{
		heredoc_cleanup(context, original);
		return (0);
	}
	if (!terminal_apply_config(&input))
	{
		heredoc_cleanup(context, original);
		return (0);
	}
	save_cursor(context);
	return (1);
}

// TODO: Check get_line error
int	heredoc_run(t_ast *redir_node, t_pipes *pipes)
{
	t_input_context	context;
	struct termios	original;

	if (!ft_strequ(redir_node->in_type, REDIR_HEREDOC))
		return (1);
	if (!heredoc_setup(&context, redir_node->in_file, &original))
		return (0);
	while (get_line(&context, 0) != INPUT_MARK_FOUND)
		display(&context);
	if (!terminal_apply_config(&original))
	{
		heredoc_cleanup(&context, &original);
		return (0);
	}
	if (write(pipes->read[PIPE_WRITE], context.input,
			ft_strlen(context.input)) == -1)
	{
		input_context_free(&context);
		return (0);
	}
	input_context_free(&context);
	return (1);
}
