/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:56:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/08 12:51:01 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// TODO: Non-canonical input mode
// TODO: Check get_line error
int	heredoc_run(t_ast *redir_node, t_pipes *pipes)
{
	t_input_context	context;

	if (!ft_strequ(redir_node->in_type, REDIR_HEREDOC))
		return (1);
	if (!input_context_set(&context, redir_node->in_file))
	{
		input_context_free(&context);
		return (0);
	}
	while (get_line(&context, 1) != INPUT_MARK_FOUND)
	{
	}
	if (write(pipes->read[PIPE_WRITE], context.input,
			ft_strlen(context.input)) == -1)
	{
		input_context_free(&context);
		return (0);
	}
	return (1);
}
