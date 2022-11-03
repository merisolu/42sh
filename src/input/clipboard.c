/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:21:42 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/03 14:28:45 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_input_result	cut_word(t_input_context *ctx)
{
	size_t	len;
	size_t	end;
	size_t	start;

	if (!(ft_strlen(ctx->input) > 0 && ctx->cursor > 0))
		return (INPUT_NO_MARK_FOUND);
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
	return (INPUT_NO_MARK_FOUND);
}

t_input_result	cut_to_cursor(t_input_context *ctx)
{
	ft_strncpy(ctx->clipboard, ctx->input, ctx->cursor);
	ctx->clipboard[ctx->cursor] = '\0';
	ft_strcpy(ctx->input, ctx->input + ctx->cursor);
	ft_bzero(ctx->input + ft_strlen(ctx->input),
		INPUT_MAX_SIZE - ctx->cursor);
	ctx->cursor = 0;
	return (INPUT_NO_MARK_FOUND);
}

t_input_result	cut_from_cursor(t_input_context *ctx)
{
	ft_strncpy(ctx->clipboard, ctx->input + ctx->cursor,
		ft_strlen(ctx->input + ctx->cursor));
	ctx->clipboard[ft_strlen(ctx->input + ctx->cursor)] = '\0';
	ft_bzero(ctx->input + ctx->cursor,
		ft_strlen(ctx->input) - ctx->cursor);
	return (INPUT_NO_MARK_FOUND);
}

t_input_result	paste(t_input_context *ctx)
{
	int	limit_reached;

	limit_reached = ft_strlen(ctx->input) + ft_strlen(ctx->clipboard)
		>= INPUT_MAX_SIZE;
	if (limit_reached)
		ctx->clipboard[INPUT_MAX_SIZE - ft_strlen(ctx->input)] = '\0';
	ft_memmove(
		ctx->input + ctx->cursor + ft_strlen(ctx->clipboard),
		ctx->input + ctx->cursor,
		ft_strlen(ctx->input + ctx->cursor));
	ft_memcpy(ctx->input + ctx->cursor, ctx->clipboard,
		ft_strlen(ctx->clipboard));
	ctx->cursor += ft_strlen(ctx->clipboard);
	if (limit_reached)
		ft_putstr(tgetstr("bl", NULL));
	return (INPUT_NO_MARK_FOUND);
}
