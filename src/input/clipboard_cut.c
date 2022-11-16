/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard_cut.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:05:38 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/16 11:05:53 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	cut_word(t_input_context *ctx)
{
	size_t	len;
	size_t	end;
	size_t	start;

	if (!(ft_strlen(ctx->input) > 0 && ctx->cursor > 0))
		return (0);
	len = ft_strlen(ctx->input);
	end = ctx->cursor - 1;
	start = end;
	while (start > 0 && start < len && ft_is_whitespace(ctx->input[start]))
		start--;
	while (start > 0 && start < len && !ft_is_whitespace(ctx->input[start]))
		start--;
	if (start > 0)
		start++;
	ft_strncpy(ctx->clipboard, ctx->input + start, end - start + 1);
	ctx->clipboard[end - start + 1] = '\0';
	ft_strncpy(ctx->input, ctx->input, start);
	ft_strcpy(ctx->input + start, ctx->input + end + 1);
	ft_bzero(ctx->input + ft_strlen(ctx->input),
		INPUT_MAX_SIZE - ft_strlen(ctx->input));
	ctx->cursor -= end - start + 1;
	return (1);
}

int	cut_to_cursor(t_input_context *ctx)
{
	ft_strncpy(ctx->clipboard, ctx->input, ctx->cursor);
	ctx->clipboard[ctx->cursor] = '\0';
	ft_strcpy(ctx->input, ctx->input + ctx->cursor);
	ft_bzero(ctx->input + ft_strlen(ctx->input),
		INPUT_MAX_SIZE - ctx->cursor);
	ctx->cursor = 0;
	return (1);
}

int	cut_from_cursor(t_input_context *ctx)
{
	ft_strncpy(ctx->clipboard, ctx->input + ctx->cursor,
		ft_strlen(ctx->input + ctx->cursor));
	ctx->clipboard[ft_strlen(ctx->input + ctx->cursor)] = '\0';
	ft_bzero(ctx->input + ctx->cursor,
		ft_strlen(ctx->input) - ctx->cursor);
	return (1);
}