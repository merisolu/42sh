/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_alt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:40:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/03 13:31:50 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	handle_alt_left_right(char buf[BUF_SIZE], t_input_context *ctx)
{
	size_t	start_limit;
	size_t	offset;
	size_t	end_limit;
	int		delta;

	start_limit = 0;
	end_limit = ft_strlen(ctx->input);
	offset = 0;
	if (ft_strnequ(buf, ARROW_LEFT_ALT, ft_strlen(ARROW_LEFT_ALT)))
	{
		offset++;
		delta = -1;
	}
	else
		delta = 1;
	while (ctx->cursor + delta >= start_limit
		&& ctx->cursor + delta < end_limit
		&& !ft_isalnum(ctx->input[ctx->cursor - offset]))
		ctx->cursor += delta;
	while (ctx->cursor + delta >= start_limit
		&& ft_isalnum(ctx->input[ctx->cursor - offset]))
		ctx->cursor += delta;
	return (3);
}

int	handle_alt_up(char buf[BUF_SIZE], t_input_context *ctx)
{
	size_t	column;
	size_t	length;
	size_t	distance;

	(void)buf;
	column = cursor_get_column(ctx, ctx->cursor);
	distance = ft_dstrchr(ctx->input, '\n', ctx->cursor);
	if (distance != ctx->cursor + 1)
		ctx->cursor = ctx->cursor - (distance + 1);
	else
		ctx->cursor = 0;
	input_get_line_properties(ctx, ctx->cursor, NULL, &length);
	if (ctx->cursor >= length - column + 1)
		ctx->cursor -= length - column + 1;
	return (6);
}

int	handle_alt_down(char buf[BUF_SIZE], t_input_context *ctx)
{
	size_t	column;
	size_t	length;
	size_t	distance;

	(void)buf;
	column = cursor_get_column(ctx, ctx->cursor);
	distance = ft_dstchr(
			ctx->input + ctx->cursor,
			'\n',
			ft_strlen(ctx->input + ctx->cursor));
	if (distance != ft_strlen(ctx->input + ctx->cursor) + 1)
		ctx->cursor += distance + 1;
	else
		ctx->cursor = ft_strlen(ctx->input);
	input_get_line_properties(ctx, ctx->cursor, NULL, &length);
	if (ctx->cursor + ft_min(column - 2, length - 1)
		< ft_strlen(ctx->input) - 1)
		ctx->cursor += ft_min(column - 2, length - 1);
	return (6);
}
