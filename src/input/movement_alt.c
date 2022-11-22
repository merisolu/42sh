/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_alt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:40:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/22 15:18:22 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	handle_alt_left(t_input_context *ctx)
{
	size_t	start_limit;
	size_t	offset;
	size_t	end_limit;
	int		delta;

	start_limit = 0;
	end_limit = ft_strlen(ctx->input);
	offset = 1;
	delta = -1;
	while (ctx->cursor + delta >= start_limit
		&& ctx->cursor + delta < end_limit
		&& !ft_isalnum(ctx->input[ctx->cursor - offset]))
		ctx->cursor += delta;
	while (ctx->cursor + delta >= start_limit
		&& ft_isalnum(ctx->input[ctx->cursor - offset]))
		ctx->cursor += delta;
	return (1);
}

int	handle_alt_right(t_input_context *ctx)
{
	size_t	start_limit;
	size_t	offset;
	size_t	end_limit;
	int		delta;

	start_limit = 0;
	end_limit = ft_strlen(ctx->input);
	offset = 0;
	delta = 1;
	while (ctx->cursor + delta >= start_limit
		&& ctx->cursor + delta < end_limit
		&& !ft_isalnum(ctx->input[ctx->cursor - offset]))
		ctx->cursor += delta;
	while (ctx->cursor + delta >= start_limit
		&& ft_isalnum(ctx->input[ctx->cursor - offset]))
		ctx->cursor += delta;
	return (1);
}

static void	apply_prompt_offset(t_input_context *ctx, int direction, \
size_t old_start)
{
	size_t	start;
	int		variance;

	input_get_line_properties(ctx, ctx->cursor, &start, NULL);
	variance = ft_strlen_int(ctx->start_prompt)
		- ft_strlen_int(ctx->multiline_prompt);
	if (start == 0 && direction == 1 && ctx->cursor > 0)
		ctx->cursor -= variance;
	else if (start != 0 && old_start == 0 && direction == -1
		&& ctx->cursor < INPUT_MAX_SIZE)
		ctx->cursor += variance;
}

int	handle_alt_up(t_input_context *ctx)
{
	size_t	temp;
	size_t	distance;
	size_t	column;

	input_get_line_properties(ctx, ctx->cursor
		+ (ctx->input[ctx->cursor] == '\n'), &temp, NULL);
	column = ctx->cursor - temp;
	distance = ft_dstrchr(ctx->input, '\n', ctx->cursor);
	if (distance == 0 && ctx->cursor > 0)
	{
		ctx->cursor--;
		distance = ft_dstrchr(ctx->input, '\n', ctx->cursor);
	}
	ctx->cursor -= ft_min_size_t(distance, ctx->cursor);
	if (ctx->cursor == 0)
		return (1);
	ctx->cursor -= ft_dstrchr(ctx->input, '\n', ctx->cursor - 1);
	input_get_line_properties(ctx, ctx->cursor, NULL, &temp);
	ctx->cursor += ft_min_size_t(column, temp);
	apply_prompt_offset(ctx, 1, 0);
	return (1);
}

int	handle_alt_down(t_input_context *ctx)
{
	size_t	start;
	size_t	length;
	size_t	distance;
	size_t	column;
	size_t	input_length;

	input_get_line_properties(ctx,
		ctx->cursor - (ctx->input[ctx->cursor] == '\n'), &start, NULL);
	column = ctx->cursor - start;
	input_length = ft_strlen(ctx->input + ctx->cursor);
	distance = ft_dstchr(ctx->input + ctx->cursor, '\n', input_length);
	if (distance == INPUT_MAX_SIZE + 1)
		distance = INPUT_MAX_SIZE;
	ctx->cursor += distance + 1;
	input_get_line_properties(ctx, ctx->cursor, NULL, &length);
	ctx->cursor += ft_min_size_t(column, length);
	if (ctx->cursor > ft_strlen(ctx->input))
		ctx->cursor = ft_strlen(ctx->input);
	apply_prompt_offset(ctx, -1, start);
	return (1);
}
