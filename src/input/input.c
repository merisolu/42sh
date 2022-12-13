/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:42:30 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/08 15:35:53 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

extern int	g_last_signal;

static int	check_mark_validity(t_input_context *ctx)
{
	int	result;
	int	end_matches;
	int	mark_on_separate_line;
	int	mark_length;
	int	input_length;

	result = ft_strequ(ctx->mark, "\n");
	if (!result)
	{
		mark_length = ft_strlen(ctx->mark);
		input_length = ft_strlen(ctx->input);
		end_matches = ft_strendequ(ctx->input, ctx->mark);
		mark_on_separate_line = (input_length <= mark_length
				|| ctx->input[input_length - mark_length - 1] == '\n');
		result = (end_matches && mark_on_separate_line);
	}
	return (result);
}

static t_input_result	append_char(char c, t_input_context *ctx)
{
	if (ft_isprint(c))
		append_input(ctx, c);
	else if (c == '\n')
	{
		if (check_mark_validity(ctx) && !is_inhibited(ctx->input))
			return (INPUT_MARK_FOUND);
		else
			append_input(ctx, c);
	}
	return (INPUT_NO_MARK_FOUND);
}

static t_input_result	get_line(t_input_context *ctx)
{
	int		read_count;
	char	buffer[BUF_SIZE + 1];
	int		i;
	int		handle_key_result;

	ft_bzero(&buffer, BUF_SIZE + 1);
	read_count = read(STDIN_FILENO, &buffer, BUF_SIZE);
	if (read_count == 0)
		return (INPUT_NOTHING_READ);
	if (check_for_reserved_sequence(buffer, ctx))
		return (INPUT_FOUND_RESERVED_SEQUENCE);
	i = 0;
	while (i < read_count)
	{
		handle_key_result = handle_key(buffer + i, ctx);
		if (handle_key_result == -1)
			return (INPUT_CALLED_FOR_EXIT);
		i += handle_key_result;
		i += parse_cursor(buffer + i, NULL);
		if (append_char(buffer[i], ctx) == INPUT_MARK_FOUND)
			return (INPUT_MARK_FOUND);
		i++;
	}
	return (INPUT_NO_MARK_FOUND);
}

t_input_result	get_input(t_input_context *ctx)
{
	t_input_result	result;

	result = get_line(ctx);
	if (result == INPUT_NO_MARK_FOUND)
		display(ctx, 0);
	if (result == INPUT_MARK_FOUND)
		return (INPUT_MARK_FOUND);
	else if (result == INPUT_READ_ERROR)
		return (print_error(1, ERRTEMPLATE_SIMPLE, ERR_LINE_READ));
	return (result);
}
