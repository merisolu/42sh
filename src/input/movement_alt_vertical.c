/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_alt_vertical.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:40:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/25 15:18:35 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	apply_prompt_offset(t_input_context *ctx, int direction)
{
	size_t	start;
	int		variance;

	input_get_line_properties(ctx, ctx->cursor, &start, NULL);
	variance = ft_strlen_int(ctx->start_prompt)
		- ft_strlen_int(ctx->multiline_prompt);
	if (start == 0 && direction == 1 && ctx->cursor > 0)
		ctx->cursor -= variance;
	else if (start != 0 && direction == -1 && ctx->cursor < INPUT_MAX_SIZE)
		ctx->cursor += variance;
}

static size_t	get_column(t_input_context *ctx)
{
	size_t	start;

	input_get_line_properties(ctx, ctx->cursor, &start, NULL);
	return (ctx->cursor - start);
}

int	handle_alt_up(t_input_context *ctx)
{
	size_t	start;
	size_t	length;
	size_t	distance;
	size_t	column;
	size_t	offset;

	input_get_line_properties(ctx, ctx->cursor, &start, NULL);
	if (start == 0)
	{
		ctx->cursor = 0;
		return (1);
	}
	offset = (ctx->cursor > 0 && ctx->input[ctx->cursor] == '\n'
			&& ctx->input[ctx->cursor - 1] != '\n');
	ctx->cursor -= offset;
	column = get_column(ctx);
	ctx->cursor -= ft_min_size_t(column + 1, ctx->cursor);
	distance = ft_dstrchr(ctx->input, '\n', ctx->cursor - 1);
	if (distance == ctx->cursor + 1)
		distance = 0;
	ctx->cursor -= ft_min_size_t(distance, ctx->cursor);
	input_get_line_properties(ctx, ctx->cursor, &start, &length);
	ctx->cursor = start + ft_min_size_t(column + offset, length);
	apply_prompt_offset(ctx, 1);
	return (1);
}

int	handle_alt_down(t_input_context *ctx)
{
	size_t	start;
	size_t	length;
	size_t	distance;
	size_t	column;
	size_t	offset;

	offset = (ctx->cursor > 0 && ctx->input[ctx->cursor] == '\n'
			&& ctx->input[ctx->cursor - 1] != '\n');
	ctx->cursor -= offset;
	input_get_line_properties(ctx, ctx->cursor, &start, NULL);
	column = get_column(ctx);
	length = ft_strlen(ctx->input + ctx->cursor);
	distance = ft_dstchr(ctx->input + ctx->cursor, '\n', length);
	distance = ft_min_size_t(distance, length);
	ctx->cursor += distance + 1;
	input_get_line_properties(ctx, ctx->cursor, NULL, &length);
	column = ft_min_size_t(column + offset, length);
	ctx->cursor += column;
	if (start == 0 && column < length)
		apply_prompt_offset(ctx, -1);
	if (ctx->cursor > ft_strlen(ctx->input))
		ctx->cursor = ft_strlen(ctx->input);
	return (1);
}
