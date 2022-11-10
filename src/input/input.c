/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:42:30 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/09 15:41:45 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

extern int	g_last_signal;

static int	is_inhibited(char *input)
{
	t_tokenizer	tokenizer;
	t_token		*tokens;

	tokens = tokenize(input, &tokenizer);
	if (!tokens)
		return (print_error(ERR_MALLOC_FAIL, 0));
	token_list_free(&tokens);
	return (tokenizer.in_quotes);
}

static void	append_input(t_input_context *ctx, char character)
{
	if (ft_strlen(ctx->input) == INPUT_MAX_SIZE)
	{
		ft_putstr(tgetstr("bl", NULL));
		return ;
	}
	ft_memmove(ctx->input + ctx->cursor + 1,
		ctx->input + ctx->cursor,
		ft_strlen(ctx->input) - ctx->cursor);
	ctx->input[ctx->cursor] = character;
	ctx->cursor++;
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
	i = 0;
	while (i < read_count)
	{
		handle_key_result = handle_key(buffer + i, ctx);
		if (handle_key_result == -1)
			return (INPUT_CALLED_FOR_EXIT);
		i += handle_key_result;
		if (i >= BUF_SIZE)
			break ;
		if (ft_isprint(buffer[i]) || buffer[i] == '\n')
		{
			append_input(ctx, buffer[i]);
			if (ft_strendequ(ctx->input, ctx->mark)
				&& !is_inhibited(ctx->input))
				return (INPUT_MARK_FOUND);
		}
		i++;
	}
	return (INPUT_NO_MARK_FOUND);
}

t_input_result	get_input(t_input_context *ctx)
{
	t_input_result	result;

	result = get_line(ctx);
	if (result == INPUT_NO_MARK_FOUND)
		display(ctx);
	if (result == INPUT_MARK_FOUND)
		return (INPUT_MARK_FOUND);
	else if (result == INPUT_READ_ERROR)
		return (print_error(ERR_LINE_READ, 1));
	return (result);
}
