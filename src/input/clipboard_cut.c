/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard_cut.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:05:38 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/08 12:58:01 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	cut_word(t_input_context *ctx)
{
	size_t	start;
	size_t	end;

	if (!(ft_strlen(ctx->input) > 0 && ctx->cursor > 0))
		return (1);
	get_word_at_cursor(ctx, &start, &end);
	copy_word(ctx);
	ft_strncpy(ctx->input, ctx->input, start);
	ft_strcpy(ctx->input + start, ctx->input + end + 1);
	ft_bzero(ctx->input + ft_strlen(ctx->input),
		INPUT_MAX_SIZE - ft_strlen(ctx->input));
	ctx->cursor -= end - start + 1;
	return (1);
}

int	cut_to_cursor(t_input_context *ctx)
{
	copy_to_cursor(ctx);
	ft_bzero(ctx->input, ctx->cursor);
	ft_strcpy(ctx->input, ctx->input + ctx->cursor);
	ctx->cursor = 0;
	return (1);
}

int	cut_from_cursor(t_input_context *ctx)
{
	copy_from_cursor(ctx);
	ft_bzero(ctx->input + ctx->cursor,
		ft_strlen(ctx->input) - ctx->cursor);
	return (1);
}
