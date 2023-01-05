/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:15:29 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/05 10:59:33 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	is_inhibited(char *input)
{
	t_tokenizer	tokenizer;
	t_token		*tokens;

	tokens = tokenize(input, &tokenizer);
	if (!tokens)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		return (print_error(0, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	}
	token_list_free(&tokens);
	return (tokenizer.in_quotes || tokenizer.backslash_inhibited);
}

void	append_input(t_input_context *ctx, char character)
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

int	check_for_reserved_sequence(char *buffer, t_input_context *ctx)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = ft_null_array_len((void **)ctx->reserved_sequences);
	while (i < length)
	{
		if (ft_strequ(buffer, ctx->reserved_sequences[i]))
		{
			ft_bzero(ctx->found_reserved_sequence, BUF_SIZE + 1);
			ft_strcpy(ctx->found_reserved_sequence, buffer);
			return (1);
		}
		i++;
	}
	return (0);
}
